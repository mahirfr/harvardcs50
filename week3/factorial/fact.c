#include <cs50.h>
#include <stdio.h>

int fact(int n)
{
    if (n == 1)
        return n;
    else if (n > 1)
    {
        return n * fact(n - 1);
    }
    else
        return -1;
}

int main(void)
{
    int n = 5;
    printf("factorial of a number: %i\n", fact(n));
}