#include <stdio.h>
#include <stdlib.h>
#include "Board.h"

int main()
{
   Trie *trie = TrieScanWordCode(&WordScore);
   BoardSolver *bs = BoardSolverInit(trie, 2000);
   Board *board;
   int i;
   
   srand(time(NULL));
   
   for (i = 0; i < 1000000; i++) {
      board = BoardRandom(bs);
   }
   
   TrieDestroy(trie);
   BoardSolverDestroy(bs);
   
   return 0;
}
