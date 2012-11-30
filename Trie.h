#include <stdio.h>

typedef struct Trie {
   char letter;
   int terminates;
   int score;
   int childCount;
   unsigned int foundInBoard;
   struct Trie *children;
} Trie;

Trie *TrieScanWordList(FILE *in);

Trie *TrieScanWordCode(FILE *in, int WordScore(int wordLength));

void TriePrintWordList(Trie *trie);

void TriePrintWordCode(Trie *trie);

void TrieDestroy(Trie *trie);

Trie *TrieGetChild(Trie *trie, char letter);
