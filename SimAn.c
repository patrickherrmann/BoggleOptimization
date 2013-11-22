#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Board.h"

#define MAX_STEPS 100000

int accept(Board *current, Board *neighbor, double t)
{
   double r, p, d;
   static int i = 1;
   int diff = BoardScore(neighbor) - BoardScore(current);
   
   if (diff >= 0) return 1;
   
   r = (double) rand() / (double) RAND_MAX;
   d = exp(diff * 0.05) - 1;
   p = 0.5 * exp(d / t);
   if (i++ % 10000 == 0) printf("d = %d\tt = %f\tp = %f\n", diff, t, p);
   return p > r;
}

int main()
{
   Trie *trie = TrieScanWordCode(stdin, &WordScore);
   BoardSolver *bs = BoardSolverInit(trie, DEFAULT_ALPHABET);
   Board *best, *current, *neighbor;
   double t;
   int step = 0;
      
   srand(time(NULL));
   
   current = BoardRandom(bs);
   best = BoardCopy(current);
   
   while (step < MAX_STEPS) {
      t = 1 - ((double) step / (double) MAX_STEPS);
      
      neighbor = BoardMutate(bs, current);
      
      if (accept(current, neighbor, t)) {
         BoardRecycle(current);
         current = neighbor;
         if (BoardScore(current) > BoardScore(best)) {
            BoardRecycle(best);
            best = BoardCopy(current);
            BoardPrintWithStats(stdout, best);
         }
      } else {
         BoardRecycle(neighbor);
      }
      step++;
   }
   
   BoardRecycle(current);
   BoardRecycle(best);
   BoardGarbageCollect();
   TrieDestroy(trie);
   BoardSolverDestroy(bs);
   
   return 0;
}
