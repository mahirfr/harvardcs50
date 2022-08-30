#include <cs50.h>
#include <stdio.h>

int get_cents(void)
{
    int input_cents;
    do
    {
        input_cents = get_int("how many cents: ");
    }
    while (input_cents < 1 || input_cents > 200);
    return input_cents;
}

int calculate_quarters(int q)
{
    return q / 25;
}

int calculate_dimes(int d)
{
    return d / 10;
}

int calculate_nickels(int n)
{
    return n / 5;
}

int calculate_pennies(int p)
{
    return p / 1;
}

int main(void)
{

    int cents = get_cents();

    // printf("input: %i\n", cents);

    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25  ;

    // printf("quarters: %i\n", quarters);

    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10 ;

    // printf("dimes: %i\n", dimes);

    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5 ;

    // printf("nickels: %i\n", nickels);

    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1 ;

    // printf("pennies: %i\n", pennies);

    int coins = quarters + dimes + nickels + pennies;

    printf("%i\n", coins);

    return 0;
}

