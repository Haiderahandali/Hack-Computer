#include "hashtable.h"

ulong_t Hash(char* key, ulong_t seed)
{
    ulong_t h = seed;

    // this function is copied from stack over flow https://stackoverflow.com/a/629127
    while (*key)
    {
        h = h * 101 + (unsigned)*key++;
    }

    return h;
}

void PrintSymbol(symbol_t* symbol)
{
    if (symbol)
    {
        printf("value = %d, key = %s\n", symbol->value, symbol->key);
        if (symbol->next)
        {
            printf("collision happened at slot %lu with key: %s and key: %s \n", Hash(symbol->key, RANDOM_SEED) % SYMBOL_SIZE, symbol->key, symbol->next->key);
            PrintSymbol(symbol->next);
        }
    }
    else
    {
        printf("Entry is currently null\n");
    }
}

void FreeSymbol(symbol_t* symbol)
{
    symbol_t* next;
    while (symbol != NULL)
    {
        next = symbol->next;
        free(symbol->key);
        free(symbol);
        symbol = next;
    }
}

symbol_table_t* CreateSymbolTable(ulong_t size)
{
    symbol_table_t* hashtable = (symbol_table_t*)malloc(sizeof(symbol_table_t) * 1);

    hashtable->symbols = malloc(sizeof(symbol_t*) * size);

    for (ulong_t i = 0; i < size; ++i)
    {
        hashtable->symbols[i] = NULL;
    }
    hashtable->size = size;
    return hashtable;
}

void DestroySymbolTable(symbol_table_t* table)
{
    if (table)
    {
        for (ulong_t i = 0, size = table->size; i < size; ++i)
        {
            FreeSymbol(table->symbols[i]);
        }
        free(table->symbols);
        free(table);
    }
}

symbol_t* AddSymbol(char* key, int value)
{
    symbol_t* symbol = (symbol_t*)malloc(sizeof(symbol_t) * 1);
    symbol->key      = (char*)malloc(sizeof(char) * (strlen(key)) + 1);
    strcpy(symbol->key, key);
    symbol->value = value;

    symbol->next = NULL;
    return symbol;
}

symbol_t* GetSymbolInHashTable(symbol_table_t* hashtable, char* key)
{
    ulong_t slot = Hash(key, RANDOM_SEED) % SYMBOL_SIZE;

    symbol_t* symbol = hashtable->symbols[slot];

    while (symbol != NULL)
    {
        if (strcmp(symbol->key, key) == 0)
        {
            return symbol;
        }
        symbol = symbol->next;
    }
    return NULL;
}

void HashtableInsertSymbol(char* key, int value, symbol_table_t* hashtable)
{
    int slot         = Hash(key, RANDOM_SEED) % SYMBOL_SIZE;
    symbol_t* symbol = hashtable->symbols[slot];
    if (symbol == NULL)
    {
        hashtable->symbols[slot] = AddSymbol(key, value);
        return;
    }

    symbol_t* prev;
    while (symbol != NULL)
    {
        if (strcmp(symbol->key, key) == 0) //found the same key, not a collision
        {
            symbol->value = value;
            return;
        }
        prev   = symbol;
        symbol = symbol->next;
    }
    prev->next = AddSymbol(key, value);
}
