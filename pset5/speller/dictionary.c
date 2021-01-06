// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

int words_num = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Hash the word to get the hash value.
    int index = hash(word);
    // Access the linked list.
    // Set cursor to the first item on the list.
    node *cursor = table[index];
    // Traverse linked list looking for the word.
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // Keep moving cursor until null.
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Take an input.
    int value = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        value += tolower(word[i]);
    }
    // Output a numerial index.
    int hash = value % N;
    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open the dictionary file.
    FILE *dict = fopen(dictionary, "r");
    // Error check while opening the file.
    if (dict != NULL)
    {
        // Initialize the Hash Table.
        for (int i = 0; i < N; i++)
        {
            table[i] = NULL;
        } 
        // Read strings from file one at a time.
        char word[LENGTH + 1];
        while (fscanf(dict, "%s", word) != EOF)
        {
            // Create a new node for each word.
            node *n = malloc(sizeof(node));
            if (n != NULL)
            {
                strcpy(n->word, word);
                n->next = NULL;
            }
            // Hash word to obtain a Hash value.
            int hash_value = hash(word);
            // Insert the node into the Hash Table at that location.
            // If the list is empty, start pointing the first element.
            if (table[hash_value] == NULL)
            {
                table[hash_value] = n;
            }
            // If the list have elements, insert the node at the front of the list.
            else
            {
                n->next = table[hash_value];
                table[hash_value] = n;
            }
            words_num++;
            
        }
        fclose(dict);
        return true;
    }
    else
    {
        return false;
    }
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words_num;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Iteration to traverse on each array of the Hash Table.
    for (int i = 0; i < N; i++)
    {
        // Free each node.
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        table[i] = NULL;
    }
    return true;
}
