#include <stdio.h>
#include <stdlib.h>
#include "SimAn.h"
#include "Board.h"

int ScoreBoard(void *board)
{
   return BoardScore((Board *) board);
}

void *BoardNeighbor(void *board, void *config)
{
   return BoardMutate((BoardSolver *) config, (Board *) board);
}

void BoardDestroy(void *board)
{
   BoardRecycle((Board *) board);
}

int main()
{
   Trie *trie = TrieScanWordCode(&WordScore);
   BoardSolver *bs = BoardSolverInit(trie);
   Board *best;
   SimAn simAn;
      
   srand(time(NULL));
   
   simAn.state = BoardRandom(bs);
   simAn.score = &ScoreBoard;
   simAn.neighbor = &BoardNeighbor;
   simAn.neighborConfig = bs;
   simAn.destroy = &BoardDestroy;
   
   best = BoardCopy(simAn.state);
   
   while (1) {
      SimAnAdvance(&simAn);
      if (ScoreBoard(simAn.state) > ScoreBoard(best)) {
         BoardRecycle(best);
         best = BoardCopy(simAn.state);
         BoardPrintWithStats(best);
      }
   }
}
