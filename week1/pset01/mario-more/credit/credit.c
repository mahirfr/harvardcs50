#include <cs50.h>
#include <stdio.h>

long extract_last_digit(long n)
{
    return n % 10;
}

long extract_left_digits(long n)
{
        return (n - extract_last_digit(n)) / 10;
}

int is_even(int n)
{
    return n % 2 == 0;
}

int main(void)
{

    //get user's input
    long number = get_long("card number: ");

    int last_two_digits = 0;    //make a variable called last two digits that we'll use below

    int i = 1, sum1 = 0, sum2 = 0;

    while (number > 0)
    {
        if (number / 10 > 0 && number / 10 < 10)
        {
            last_two_digits = number;
        }
        if (is_even(i)) //luhn's algorithm tell's us to multiply every second digit by 2 AND we get every second digit by using is_even
        {
            int p = number % 10 * 2; //if the var p is >= 10 we have to further divide it into two digits
            if (extract_left_digits(p) == 0) //if var p < 10 we add the p to sum2
            {
                sum2 += p;
            }
            else    //if p >= 10 we further divide it in two digits
            {
                sum2 += extract_left_digits(p);
                sum2 += p % 10;
            }
        }
        else    //sum1 for every second digit starting from last digit (and including the last digit)
        {
            sum1 += number % 10;
        }
        i++;
        number = extract_left_digits(number);   //putting extract_left_digits at the end of our while loop avoids skipping the last number if it were at the begining of the while loop
    }

    int number_of_digits = i - 1;   //because we're starting the counter i from 1 we need to subtract 1

    if (((sum1 + sum2) % 10 == 0) && (number_of_digits == 16 || number_of_digits == 13) && (last_two_digits / 10 == 4))
    {
        printf("VISA\n");
    }
    else if (((sum1 + sum2) % 10 == 0) && (number_of_digits == 16) && (last_two_digits == 51 || last_two_digits == 52 || last_two_digits == 53 || last_two_digits == 54 || last_two_digits == 55))
    {
        printf("MASTERCARD\n");
    }
    else if (((sum1 + sum2) % 10 == 0) && (number_of_digits == 15) && (last_two_digits == 34 || last_two_digits == 37))
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}