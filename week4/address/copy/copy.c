#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char *s = get_string("s: ");
    char *t = malloc(strlen(s) + 1);
    if (t == NULL)
    {
        return 1;
    }

    strcpy(t, s); // or we can use a for loop like below

    //for (int i = 0, n = strlen(s) + 1; i < n; i++)
    //{
    //      t[i] = s[i];
    //}

    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("t: %s\n", t);

    free(t);

}