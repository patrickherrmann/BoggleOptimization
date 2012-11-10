#include <stdio.h>
#include "Board.h"

int main(int argc, char **argv)
{
   Board *board;
   BoardSolver *bs = BoardSolverInit(TrieScanWordCode(&WordScore), 1500);
   
   if (argc == 1) {
      board = BoardRandom(bs);
   } else {
      board = BoardFromLetters(bs, argv[1]);
   }
   BoardPrint(board);
   printf("Words: %d\nScore: %d\n", BoardWordCount(board), BoardScore(board));
}
