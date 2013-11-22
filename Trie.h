#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>

typedef struct Trie {
   char letter;
   int terminates;
   int score;
   int childCount;
   unsigned int foundInBoard;
   struct Trie *children;
} Trie;

Trie *TrieScanWordList(FILE *stream);

Trie *TrieScanWordCode(FILE *stream, int WordScore(int wordLength));

void TriePrintWordList(FILE *stream, Trie *trie);

void TriePrintFoundWords(FILE *stream, Trie *trie, unsigned long bid);

void TriePrintWordCode(FILE *stream, Trie *trie);

void TrieDestroy(Trie *trie);

Trie *TrieGetChild(Trie *trie, char letter);

#endif
