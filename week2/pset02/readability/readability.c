#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float calculate_average(float x, int y);

int main(void)
{
    string input = get_string("Text: ");

    int n_of_letters = count_letters(input);
    int n_of_words = count_words(input);
    int n_of_sentences = count_sentences(input);

    float L = calculate_average(n_of_letters, n_of_words);
    float S = calculate_average(n_of_sentences, n_of_words);

    double index = 0.0588 * L - 0.296 * S - 15.8;

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

int count_letters(string text)
{
    int count = 0;
    int n = strlen(text);
    for (int i = 0; i < n; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 0;
    int n = strlen(text);
    for (int i = 0; i < n; i++)
    {
        if (text[i] == 32)
        {
            count++;
        }
    }
    count++;
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    int n = strlen(text);
    for (int i = 0; i < n; i++)
    {
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            count++;
        }
    }
    return count;
}

float calculate_average(float x, int y)
{
    return x / y * 100;
}