#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    char c;
    struct node *next;
}
node;

const int SIZE_OF_TABLE = 9;

node *table[SIZE_OF_TABLE];

node *create(int value)
{
    if (value > 8 || value < 0)
    {
        return false;
    }

    node *node = malloc(sizeof(node));

    if (value > 1)
    {
        node->c = 'a';
        node->next = create(value - 1);
    }
    else
    {
        node->c = 'b';
        node->next = NULL;
    }
    return node;
}

void print_nodes(node *node, int value)
{
    if (node == NULL)
    {
        return;
    }
    if (value == 0)
    {
        return;
    }
    printf("%c\n", node->c);
    print_nodes(node->next, value - 1);
}



int main(void)
{
    int value = 8;
    node *n = create(value);
    print_nodes(n, value);
}