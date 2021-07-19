#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYMBOL_SIZE 1000
#define RANDOM_SEED 1751379 // can be set to anything really
typedef unsigned long ulong_t;

typedef struct symbol_t
{
    char* key;
    int value;
    struct symbol_t* next;
} symbol_t;

typedef struct symbol_table_t
{
    symbol_t** symbols;
    ulong_t size;
} symbol_table_t;

void PrintSymbol(symbol_t* entry);
void FreeSymbol(symbol_t* symbol);
void DestroySymbolTable(symbol_table_t* table);
void HashtableInsertSymbol(char* key, int value, symbol_table_t* hashtable);

symbol_t* AddSymbol(char* key, int value);
symbol_table_t* CreateSymbolTable(ulong_t size);
symbol_t* GetSymbolInHashTable(symbol_table_t* hashtable, char* key);
ulong_t Hash(char* key, ulong_t seed);

#endif
