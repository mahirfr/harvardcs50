#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool is_input_valid(string s);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (!is_input_valid(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // function checking for non unique chars
    for (int i = 0; i < 26; i++)
    {
        if (argv[1][i])
        {
            for (int j = i + 1; j < 26; j++)
            {                                   // for input of lower-case          for input of upper-case
                if(argv[1][i] == argv[1][j] || argv[1][i] == argv[1][j] - 32 || argv[1][i] == argv[1][j] + 32)
                {
                    printf("Error: repeating characters\n");
                    return 1;
                }
            }
        }
    }

    char alphabet_upper[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                         'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                         'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    char alphabet_lower[26] = {'a','b', 'c', 'd', 'e', 'f', 'g', 'h',
                               'i', 'j','k', 'l', 'm', 'n', 'o', 'p',
                               'q', 'r', 's','t', 'u', 'v', 'w', 'x',
                               'y', 'z'};

    string plain = get_string("plaintext:  ");

    const int key = strlen(argv[1]);
    const int n_of_letters = 26;

    printf("ciphertext: ");

        // function for replacing letters !
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        for (int j = 0; j < n_of_letters; j++)
        {
            if (plain[i] == alphabet_upper[j])
            {
                for (int o = 0; o < key; o++)
                {
                    if (j == o)
                    {
                        printf("%c", toupper(argv[1][o]));
                    }
                }
            }
            if (plain[i] == alphabet_lower[j])
            {
                for (int o = 0; o < key; o++)
                {
                    if (j == o)
                    {
                        printf("%c", tolower(argv[1][o]));
                    }
                }
            }
        }
        // prints non alphabetical chars
        if (!isalpha(plain[i]))
        {
            printf("%c", plain[i]);
        }
    }
    printf("\n");
    return 0;
}

bool is_input_valid(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalpha(s[i]) && (n == 26))
        {
            return true;
        }
    }
    return false;
}