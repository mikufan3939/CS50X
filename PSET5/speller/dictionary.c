// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

unsigned int dictionarySize = 0;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 7919;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashNumber;
    node *aux;
    hashNumber = hash(word);
    if (table[hashNumber] == NULL)
    {
        return false;
    }
    else
    {
        aux = table[hashNumber];
        while (aux)
        {
            if (strcasecmp(aux->word, word) == 0)
            {
                return true;
            }
            aux = aux->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int key = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] != '\n')
        {
            key = key + (toupper(word[i]) * (45 - i));
        }
    }
    return key % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dictionaryFile = fopen(dictionary, "r");
    int hashIndex;
    char c;
    char word[LENGTH + 1];

    if (dictionaryFile == NULL)
    {
        return false;
    }
    else
    {
        while (fgets(word, 47, dictionaryFile))
        {
            node *newWord = malloc(sizeof(node));
            if (newWord == NULL)
            {
                return false;
            }
            word[strcspn(word, "\n")] = 0;
            strcpy(newWord->word, word);
            hashIndex = hash(newWord->word);

            if (table[hashIndex] == NULL)
            {
                table[hashIndex] = newWord;
                newWord->next = NULL;
            }
            else
            {
                newWord->next = table[hashIndex];
                table[hashIndex] = newWord;
            }
            dictionarySize = dictionarySize + 1;
        }
    }
    fclose(dictionaryFile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionarySize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *aux;
    for (int i = 0; i <= N; i++)
    {
        aux = table[i];
        while (aux != NULL)
        {
            aux = table[i]->next;
            free(table[i]);
            table[i] = aux;
        }
    }
    free(aux);
    return true;
}
