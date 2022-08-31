import re


def main():
    number_list = []
    while True:
        num = input("Card number: ")
        if re.search(r'^[0-9]+$', num):
            break
    number = int(num)
    for i in range(len(num)):
        last = last_digit(number)
        number_list.append(last)
        number = extract_left_digits(number)
    print(number_list)
    sum = sum1(number_list) + sum2(number_list)
    print(sum)
    if len(number_list) == 16 and last_digit(sum) == 0 and number_list[15] == 5 and (number_list[14] == 1 or number_list[14] == 2 or number_list[14] == 3 or number_list[14] == 4 or number_list[14] == 5):
        print("MASTERCARD")
    elif (len(number_list) == 13 or len(number_list) == 16) and last_digit(sum) == 0 and (number_list[15] == 4 or number_list[12] == 4):
        print("VISA")
    elif len(number_list) == 15 and last_digit(sum) == 0 and number_list[14] == 3 and (number_list[13] == 4 or number_list[13] == 7):
        print("AMEX")
    else:
        print("INVALID")


def sum1(number_list):
    sum1 = 0
    for i in range(0, len(number_list), 2):
        sum1 += number_list[i]
    return sum1


def sum2(number_list):
    sum2 = 0
    for i in range(1, len(number_list), 2):
        if number_list[i] * 2 >= 10:
            bigger_num = number_list[i] * 2
            sum2 += last_digit(bigger_num) + extract_left_digits(bigger_num)
        else:
            sum2 += number_list[i] * 2
    return sum2


def last_digit(number):
    return number % 10


# Extracts left digits one at a time
def extract_left_digits(number):
    return int((number - last_digit(number)) / 10)


if __name__ == "__main__":
    main()