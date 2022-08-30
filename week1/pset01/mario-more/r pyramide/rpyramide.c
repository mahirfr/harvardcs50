#include <stdio.h>
#include <cs50.h>

int main (void)
{
    int h;
    //prompt the user for input
    do
    {
        h = get_int("Height(1-8): ");
    }
    //limits the input from 1 to 8
    while (h < 1 || h > 8);

    for(int r = 0; r < h; r++)
    {
        for(int c = 0; c <= r; c++)
        {
            printf("#");
        }
        for(int sp = h - 1; sp > r; sp--)
        {
            printf(".");
        }
        printf("..");
        for(int sp2 = h - 1; sp2 > r; sp2--)
        {
            printf(".");
        }
        for(int c2 = 0; c2 <= r; c2++)
        {
            printf("#");
        }
        printf("\n");
    }
}