#include <stdio.h>
#include <stdlib.h>
#include "Board.h"

int main()
{
   Trie *trie = TrieScanWordCode(&WordScore);
   BoardSolver *bs = BoardSolverInit(trie, 1500);
   Board *board;
   
   srand(time(NULL));
   
   board = BoardRandom(bs);
   
   BoardPrint(board);
   
   printf("Word count: %d\n", BoardWordCount(board));
   
   TrieDestroy(trie);
   
   return 0;
}
