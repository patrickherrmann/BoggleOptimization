#include <stdlib.h>
#include "WordHashTable.h"

struct WordHashTable {
   void **entries;
   int capacity;
   int allocated;
   int size;
};

static int isPrime(int n)
{
   int i;
   
   for (i = 3; i * i <= n; i += 2)
      if (n % i == 0)
         return 0;
   
   return 1;
}

static int nextPrime(int n)
{
   if (n < 3) return 3;
   if (n % 2 == 0) n++;
   
   while (!isPrime(n))
      n += 2;
   
   return n;
}

WordHashTable *WordHashTableInit(int capacity)
{
   WordHashTable *wht = malloc(sizeof(wht));
   
   wht->capacity = capacity;
   wht->size = 0;
   wht->allocated = nextPrime(capacity * 2);
   wht->entries = calloc(sizeof(void *), wht->allocated);
   
   return wht;
}

void WordHashTableDestroy(WordHashTable *wht)
{
   free(wht->entries);
   free(wht);
}

int findPosition(int allocated, void *data)
{
   int pos = ((int) data) % allocated;
   
   if (pos < 0)
      pos += allocated;
   
   return pos;
}

int quadraticProbe(WordHashTable *wht, void *data)
{
   int offset = 1;
   int current = findPosition(wht->allocated, data);
   
   while (wht->entries[current] && wht->entries[current] != data) {
      current += offset;
      offset += 2;
      current %= wht->allocated;
   }
   return current;
}

void WordHashTableAdd(WordHashTable *wht, void *data)
{
   int pos = quadraticProbe(wht, data);
   
   if (!wht->entries[pos])
      wht->size++;
   
   wht->entries[pos] = data;
}

int WordHashTableContains(WordHashTable *wht, void *data)
{
   return wht->entries[quadraticProbe(wht, data)] != NULL;
}

int WordHashTableSize(WordHashTable *wht)
{
   return wht->size;
}

void WordHashTableClear(WordHashTable *wht)
{
   int i = wht->allocated;
   
   while (i--)
      wht->entries[i] = NULL;
   
   wht->size = 0;
}
