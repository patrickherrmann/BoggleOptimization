#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Board.h"

int main()
{
   Trie *trie = TrieScanWordCode(stdin, &WordScore);
   BoardSolver *bs = BoardSolverInit(trie, DEFAULT_ALPHABET);
   Board *board;
   int i;
   
   srand(time(NULL));
   
   for (i = 0; i < 1000000; i++) {
      board = BoardRandom(bs);
      BoardRecycle(board);
   }
   
   BoardGarbageCollect();
   TrieDestroy(trie);
   BoardSolverDestroy(bs);
   
   return 0;
}
