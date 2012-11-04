#include <stdio.h>
#include "Trie.h"

int main() {
   Trie *trie = TrieScanWordCode();
   TriePrintWordList(trie);
   TrieDestroy(trie);
}
