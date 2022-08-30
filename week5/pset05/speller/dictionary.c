// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents count of words in dictionary
unsigned int words_in_dictionary = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 17576;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    for (node *tmp = table[hash(word)]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
            return true;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int sum = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {

        sum += tolower(word[i]) * 7;
    }
    return sum % N;
    // if (strlen(word) >= 3)
    // {
    //    return (((tolower(word[0]) - 'a' + 1) * 26 + (tolower(word[1]) - 'a' + 1) * 26  + (tolower(word[2]) - 'a' + 1) * 26) - 1) % N;
    // }
    // else if (strlen(word) == 2)
    // {
    //     return (((tolower(word[0]) - 'a' + 1) * 26 + (tolower(word[1]) - 'a' + 1) * 26) - 1) % N;
    // }
    // else
    //     return (((tolower(word[0]) - 'a' + 1) * 26) - 1) % N;
}

node *create(const char *word)
{
    node *n = malloc(sizeof(node));
    if (n != NULL)
    {
        strcpy(n->word, word);
        n->next = NULL;
    }
    return n;
}

void insert(node *node)
{
    unsigned int index = hash(node->word);
    node->next = table[index];
    table[index] = node;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    // Initialises the hash table to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_node = create(word);
        insert(new_node);
        words_in_dictionary++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words_in_dictionary;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while(table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
