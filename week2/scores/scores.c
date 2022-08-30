#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int size = get_int("How many scores? "), i;

    float scores[size];

    for (i = 0; i < size; i++)
    {
        scores[size] += get_int("scores: ");
    }
    printf("average: %f\n", scores[size] / size);
}