typedef struct Trie {
   char letter;
   int terminates;
   int score;
   int childCount;
   struct Trie *children;
} Trie;

Trie *TrieScanWordList();

Trie *TrieScanWordCode(int WordScore(int wordLength));

void TriePrintWordList(Trie *trie);

void TriePrintWordCode(Trie *trie);

void TrieDestroy(Trie *trie);

Trie *TrieGetChild(Trie *trie, char letter);
