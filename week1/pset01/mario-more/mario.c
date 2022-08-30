#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    //prompt the user for input
    do
    {
        h = get_int("Height(1-8): ");
    }
    //limits the input from 1 to 8
    while (h < 1 || h > 8);
    //first for loop makes spaces and goes to a new line
    for (int r = 0; r < h; r++)
    {
        //right-alligned pyramid for loop
        for (int sp = 0; sp < h - r - 1; sp++)
        {
            printf(".");
        }
        for (int c = 0; c <= r; c++)
        {
            printf("#");
        }
        printf("..");
        //left-alligned pyramid for loop
        for (int c = 0; c <= r; c++)
        {
            printf("#");
        }
        rintf("\n");
    }p
}