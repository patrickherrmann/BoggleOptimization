#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Board.h"

/* The algorithm will halt after solving this many boards */
#define MAX_STEPS 100000

#define TRIMMED_ALPHABET "acdegilmnoprst"

/*
   Losing this percent of a board's score will be accepted with
   probability 1/e. Thus a higher percentage will result in more
   willing acceptance of worse boards. Note that this is at
   maximum temperature; as the temperature lowers, actual probability
   of acceptance is much lower.
*/
#define A 0.05

int accept(Board *current, Board *neighbor, double t)
{
   double r, p;
   int currentScore = BoardScore(current);
   int diff = BoardScore(neighbor) - currentScore;
   
   if (diff >= 0) return 1;
   
   r = (double) rand() / (double) RAND_MAX;
   p = exp(diff / (A * currentScore * t));
   return p > r;
}

int main()
{
   Trie *trie = TrieScanWordCode(stdin, &WordScore);
   BoardSolver *bs = BoardSolverInit(trie, TRIMMED_ALPHABET);
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
