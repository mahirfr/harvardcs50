#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h, c;
    //prompt the user for input
    do
    {
        h = get_int("Height(1-8): ");
    }
    //limits the input from 1 to 8
    while (h < 1 || h > 8);

    for (int r = 0; r < h; r++)
    {
        for (c = h; c > r; c--)
        {
            printf("#");
        }
        for (int sp = 0; sp < c; sp++)
        {
            printf(".");
        }
        printf("..");
        for (int sp2 = 0; sp2 < c; sp2++)
        {
            printf(".");
        }
        for(int c2 = h; c2 > r; c2--)
        {
            printf("#");
        }
        printf("\n");
    }
}