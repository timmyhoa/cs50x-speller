// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 108000;

// Hash table
node *table[N];

unsigned int count = 0;

void convert(char *word)
{
    for (int i = 0; word[i] != 0; i++)
    {
        word[i] = tolower(word[i]);
    }
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    char temp[strlen(word) + 1];
    strcpy(temp, word);
    convert(temp);
    int index = hash(temp);
    for (node *temp1 = table[index]; temp1 != NULL; temp1 = temp1 -> next)
    {
        if (strcasecmp(temp1 -> word, word) == 0) return true;
    }
    return false;
}



// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    // while ((c = tolower(*word++)))
    while ((c = *word++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dic = fopen(dictionary, "r");
    if (dic == 0) return false;

    char *word = malloc(46);

    while (fscanf(dic, "%s", word) != EOF)
    {
        int index = hash(word);

        node *current = malloc(sizeof(node));
        if (current == 0) return false;

        strcpy(current -> word, word);
        if (table[index] == 0)
        {
            table[index] = current;
            current -> next = 0;
        }
        else
        {
            current -> next = table[index];
            table[index] = current;
        }
        count++;
    }
    free(word);
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (unsigned int i = 0; i < N; i++)
    {
        node *temp = table[i];
        node *temp1 = NULL;
        while (temp != NULL)
        {
            temp1 = temp -> next;
            free(temp);
            temp = temp1;
        }
    }
    return true;
}
