#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Board.h"

#define MAX_STEPS 100000

int accept(Board *current, Board *neighbor, double t) {
   double r, p;
   int diff = BoardScore(neighbor) - BoardScore(current);
   if (diff) printf("%d\n", diff);
   if (diff >= 0) return 1;
   
   r = (double) rand() / (double) RAND_MAX;
   p = exp(diff / t);
   return p > r;
}

int main()
{
   Trie *trie = TrieScanWordCode(stdin, &WordScore);
   BoardSolver *bs = BoardSolverInit(trie);
   Board *best, *current, *neighbor;
   double t;
   int step = 0;
      
   srand(time(NULL));
   
   current = BoardRandom(bs);
   best = BoardCopy(current);
   
   while (step < MAX_STEPS) {
      t = 1 - (step / MAX_STEPS);
      
      neighbor = BoardMutate(bs, current);
      
      if (accept(current, neighbor, t)) {
         BoardRecycle(current);
         current = neighbor;
         /*if (BoardScore(current) > BoardScore(best)) {
            BoardRecycle(best);
            best = BoardCopy(current);
            BoardPrintWithStats(stdout, best);
         }*/
      }
      BoardRecycle(neighbor);
      step++;
   }
   
   BoardPrintWithStats(stdout, current);
}
