#include <stdio.h>
#include <stdlib.h>
#include "Board.h"

int main()
{
   Trie *trie = TrieScanWordCode();
   BoardSolver *bs = BoardSolverInit(trie);
   Board *board;
   
   srand(time(NULL));
   
   board = BoardRandom(bs);
   
   printf("Word count: %d\n", BoardWordCount(board));
   
   TrieDestroy(trie);
   
   return 0;
}
