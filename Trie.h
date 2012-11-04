typedef struct Trie {
   char letter;
   int terminates;
   int score;
   int childCount;
   struct Trie *children;
} Trie;

Trie *TrieScanWordList();
Trie *TrieScanWordCode();

void *TriePrintWordList(Trie *trie);
void *TriePrintWordCode(Trie *trie);
void TrieDestroy(Trie *trie);
