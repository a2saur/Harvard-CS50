// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 234;

// Hash table
node *table[N];

int num_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *current_node = table[hash(word)];
    while (true)
    {
        if (strcasecmp(current_node->word, word) == 0)
        {
            return true;
            break;
        }
        else
        {
            if (current_node->next != NULL)
            {
                current_node = current_node->next;
            }
            else
            {
                break;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // basic 26 values -- based on first letter
    // return toupper(word[0]) - 'A';

    // 234 values -- based on first letter + 9 length bits (by 5)
    int s = sizeof(word) / 5;
    return (s * 5) + (toupper(word[0]) - 'A');

    // 676 values -- based on first + second letter
    // return (toupper(word[0]) - 'A') + ((toupper(word[0]) - 'A')*26);

    // 6084 values -- based on first letter + 9 length bits (by 5)
    // int s = sizeof(word)/5;
    // return (s * 5) + (toupper(word[0]) - 'A') + ((toupper(word[0]) - 'A')*26);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open file
    FILE *word_file = fopen(dictionary, "r");
    if (word_file == NULL)
    {
        return false;
    }

    // get word
    char word[LENGTH];
    while (fscanf(word_file, "%s", word) != EOF)
    {
        num_words++;
        // allocate memory for node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // copy word into node
        strcpy(n->word, word);

        // put node into table
        if (table[hash(word)] == NULL)
        {
            n->next = NULL;
        }
        else
        {
            // add pointer?
            n->next = table[hash(word)];
        }
        table[hash(word)] = n;
    }

    fclose(word_file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return num_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *current_node;
    node *temp;
    for (int i = 0; i < N; i++)
    {
        current_node = table[i];
        temp = table[i];
        while (true)
        {
            temp = current_node;
            if (current_node == NULL)
            {
                break;
            }
            else if (current_node->next == NULL)
            {
                free(current_node);
                break;
            }
            else
            {
                current_node = current_node->next;
            }
            free(temp);
        }
    }
    return true;
}
