#include <stdio.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//this didn't work because it was declared locally (meaning inside the function)
//swap_not_really doesn't actually do anything with the result and the function ends
void swap_not_really(int a, int b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

int main()
{
    int x = 1;
    int y = 2;

    printf("this is x: %i, and this is y: %i\n", x, y);
    swap_not_really(x, y);
    printf("this is supposed to be swapped x: %i, supposed to be swapped y: %i\n", x, y);
    swap(&x, &y);
    printf("this is now x: %i, and this is now y: %i\nboth swapped\n", x, y);
}