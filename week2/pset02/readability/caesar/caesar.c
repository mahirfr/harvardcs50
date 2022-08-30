#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string s);
char rotate(char c, int p);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    if (only_digits(argv[1]))
    {
        int int_argv = atoi(argv[1]);

        string plain = get_string("plaintext:  "); //use a strlen to extract every char

        printf("ciphertext: ");

        for (int i = 0, n = strlen(plain); i < n; i++)
        {
            char cipher = rotate(plain[i], int_argv); //rotate function for every char in string (array of chars) plain
            printf("%c", cipher);
        }
        printf("\n");
        return 0;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

}

bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int p)
{
    if (isalpha(c))
    {
        if (isupper(c))
        {
            c = c - 'A';
            c = (c + p) % 26;
            c = c + 'A';
            return c;
        }
        else if (islower(c))
        {
            c = c - 'a';
            c = (c + p) % 26;
            c = c + 'a';
            return c;
        }
    }
    return c;
}