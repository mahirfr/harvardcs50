import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    transactions = db.execute("SELECT price, symbol, SUM(shares) AS shares, name FROM purchases WHERE user_id = ? GROUP BY name", user_id)
    current = {}
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    total_cash = 0.0

    if len(transactions) < 1:
        return render_template("index.html", cash=float(cash[0]["cash"]), totalCash=cash[0]["cash"]+total_cash)

    else:
        for transaction in transactions:
            current[transaction["symbol"]] = lookup(transaction["symbol"])["price"]
            total_cash += current[transaction["symbol"]] * transaction["shares"]
            if total_cash == 0:
                return render_template("index.html", cash=float(cash[0]["cash"]), totalCash=cash[0]["cash"]+total_cash)
        if request.method == "POST":
            if buy():
                return render_template("index.html", transactions=transactions, current=current, cash=cash[0]["cash"], totalCash=total_cash+cash[0]["cash"])

        else:
            return render_template("index.html", transactions=transactions, current=current, cash=cash[0]["cash"], totalCash=total_cash+cash[0]["cash"])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    symbol = request.form.get("symbol")
    shares = request.form.get("shares", type=int)
    user_id = session["user_id"]

    if request.method == "POST":

        if lookup(symbol) == None:
            return apology("Stock symbol not found")

        if not shares or shares < 1:
            return apology("Enter a positive integer bigger than 0")

        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        price = lookup(symbol)["price"]

        if cash[0]["cash"] - price * shares < 0:
            return apology("Not enough cash :(")
        else:
            cash_left = cash[0]["cash"] - price * shares
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_left, user_id)
            db.execute("INSERT INTO purchases (user_id, price, symbol, shares, name, ts) VALUES(?, ?, ?, ?, ?, CURRENT_TIMESTAMP)",
                        user_id, price, symbol, shares, lookup(symbol)["name"])
            return redirect("/")
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]

    transactions = db.execute("SELECT symbol, shares, price, ts FROM purchases WHERE user_id = ?", user_id)

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    symbol = request.form.get("symbol")

    if request.method == "POST":

        if lookup(symbol) != None:
            return render_template("quoted.html", symbol=lookup(symbol))
        else:
            return apology("Stock symbol not found")

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    if request.method == "POST":

        if len(username) < 5:
            return apology("username too short")

        user = db.execute("SELECT username FROM users WHERE username = ?", username)

        if len(user) != 0:
            return apology("username already exsits")

        if len(password) < 5:
            return apology("password too short")

        if password != confirmation:
            return apology("passwords do not match")

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, generate_password_hash(password))
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    symbol = request.form.get("symbol")
    shares = request.form.get("shares", type=int)
    user_id = session["user_id"]

    users = db.execute("SELECT symbol, SUM(shares) AS shares FROM purchases WHERE user_id = ? GROUP BY name", user_id)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

    if request.method == "POST":
        if not symbol:
            return apology("Enter a stock symbol")
        for user in users:
            if symbol in user["symbol"]:
                if (user["shares"] - shares) < 0:
                    return apology("Invalid number of stocks")
                else:
                    total_price = lookup(symbol)["price"] * shares
                    if total_price == 0:
                        return render_template("index.html")
                    db.execute("INSERT INTO purchases (user_id, shares, symbol, price, name, ts) VALUES(?, ?, ?, ?, ?, CURRENT_TIMESTAMP)",
                                user_id, shares-2*shares, symbol, lookup(symbol)["price"], lookup(symbol)["name"])
                    db.execute("UPDATE users SET cash = ? WHERE id = ?", cash[0]["cash"]+total_price, user_id)
                    return redirect("/")
            else:
                return apology("Invalid stock symbol")
    else:
        return render_template("sell.html", users=users)

