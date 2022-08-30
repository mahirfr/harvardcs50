#include <cs50.h>
#include <stdio.h>

int string_lenght(string s)
{
    int i = 0;
    while(s[i] != '\0')
    {
        i++;
    }
    return i;
}

int main(void)
{
    string name = get_string("Name: ");
    int lenght = string_lenght(name);
    printf("%i\n", lenght);

}