#include <cs50.h>
#include <stdio.h>

int colatz(int n)
{
        if (n == 1)
            return 0;

        else if (n % 2 == 0)
            return 1 + colatz(n/2);

        else
            return 1 + colatz(3*n + 1);
}

int main(void)
{
    int n = 100;
    int steps = colatz(n);
    printf("This is how many steps it took: %i\n", steps);
}