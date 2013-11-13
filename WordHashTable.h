#ifndef WORD_HASH_TABLE_H
#define WORD_HASH_TABLE_H

typedef struct WordHashTable WordHashTable;

WordHashTable *WordHashTableInit(int capacity);

void WordHashTableDestroy(WordHashTable *wht);

void WordHashTableAdd(WordHashTable *wht, void *data);

int WordHashTableContains(WordHashTable *wht, void *data);

int WordHashTableSize(WordHashTable *wht);

void WordHashTableClear(WordHashTable *wht);

#endif
