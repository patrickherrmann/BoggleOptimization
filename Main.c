#include <stdio.h>
#include "Trie.h"
#include "WordHashTable.h"

int main()
{
   int x = 5, y = 10;
   WordHashTable *wht = WordHashTableInit(20);
   WordHashTableAdd(wht, &x);
   WordHashTableAdd(wht, &y);
   WordHashTableAdd(wht, &x);
   printf("%d\n", WordHashTableSize(wht));
   WordHashTableClear(wht);
   WordHashTableAdd(wht, &y);
   WordHashTableAdd(wht, &y);
   printf("%d\n", WordHashTableSize(wht));
   WordHashTableDestroy(wht);
}
