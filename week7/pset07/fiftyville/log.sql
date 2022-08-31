-- Keep a log of any SQL queries you execute as you solve the mystery.

-- This one gave 5 results, the 3rd was CS50's duck ! 10:15, Humphrey Street bakery, 3 witnesses.
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28;

-- This query gave 8 licence plates, minutes: 16, 18, 18, 19, 20, 21, 23, 23
/*  | 5P2BI95       | 16     |
    | 94KL13X       | 18     |
    | 6P58WS2       | 18     |
    | 4328GD8       | 19     |
    | G412CB7       | 20     |
    | L93JTIZ       | 21     |
    | 322W7JE       | 23     |
    | 0NTHK55       | 23        */
SELECT license_plate, minute FROM bakery_security_logs WHERE day = 28 AND month = 7 AND hour = 10;

-- Witness interviews query from Ruth: within 10 min the thief left the backery. Eugene: thief has been seen on Leggett Street's ATM where he made a withdrawl, earlier in the morning. Raymond: call to acomplice, duration < 1mn, earliest
-- flight out of Fiftyville on day 29.
SELECT name, transcript FROM interviews WHERE day = 28 AND month = 7 AND transcript LIKE '%bakery%';

-- Query gives 9 calls where duration is < 1mn
SELECT caller, receiver, duration FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60;

-- Earliest flight from Fiftyville was at 8:20 on day 29, month 7 and was headed to LaGuardia Airport (airport.id: 4, flights.id: 36)
/*  +------------------------+-------------------+----+
    | destination_airport_id |     full_name     | id |
    +------------------------+-------------------+----+
    | 4                      | LaGuardia Airport | 36 |
    +------------------------+-------------------+----+ */

SELECT destination_airport_id, full_name, flights.id FROM airports
    JOIN flights ON flights.destination_airport_id = airports.id
WHERE origin_airport_id IN
    (SELECT id FROM airports WHERE city ='Fiftyville' AND day = 29 AND month = 7 AND hour = 8 AND minute = 20);

-- Suspects from flight.
/*
+------------------------+-------------------+-----------------+
| destination_airport_id |     full_name     | passport_number |
+------------------------+-------------------+-----------------+
| 4                      | LaGuardia Airport | 7214083635      |
| 4                      | LaGuardia Airport | 1695452385      |
| 4                      | LaGuardia Airport | 5773159633      |
| 4                      | LaGuardia Airport | 1540955065      |
| 4                      | LaGuardia Airport | 8294398571      |
| 4                      | LaGuardia Airport | 1988161715      |
| 4                      | LaGuardia Airport | 9878712108      |
| 4                      | LaGuardia Airport | 8496433585      |
+------------------------+-------------------+-----------------+ */
SELECT destination_airport_id, full_name, passport_number FROM airports
JOIN flights ON flights.destination_airport_id = airports.id
JOIN passengers ON passengers.flight_id = flights.id WHERE origin_airport_id IN
(SELECT id FROM airports WHERE city ='Fiftyville' AND day = 29 AND month = 7 AND hour = 8 AND minute = 20);


-- The city they escaped to is New York City

SELECT city FROM airports WHERE full_name ='LaGuardia Airport';
/*
+---------------+
|     city      |
+---------------+
| New York City |
+---------------+ */

-- The query gives out Bruce as the theif

SELECT name, account_number FROM bank_accounts
    JOIN people ON people.id = bank_accounts.person_id
        WHERE account_number IN
            (SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 AND atm_location ='Leggett Street' AND transaction_type ='withdraw' AND passport_number IN
            (SELECT passport_number FROM passengers WHERE flight_id = 36 AND phone_number IN
            (SELECT caller FROM phone_calls WHERE day = 28 AND month = 7 AND duration < 60 AND license_plate IN
            (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND hour = 10 AND minute BETWEEN 16 AND 23))));


-- This query gives us the receiver from the call that took place on 28/07/2021 and that lasted less than a minute
/*
+-------+
| name  |
+-------+
| Robin |
+-------+ */

SELECT name FROM people WHERE phone_number IN
   (SELECT receiver FROM phone_calls WHERE caller IN
        (SELECT phone_number FROM people WHERE name ='Bruce' AND day = 28 AND month = 7 AND duration < 60));