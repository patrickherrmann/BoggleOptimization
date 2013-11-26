#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Board.h"

#define TRIMMED_ALPHABET "acdegilmnoprst"
#define POP_SIZE 2000
#define GENERATIONS 200

int compareBoards(const void *b1, const void *b2)
{
   return BoardScore(*(Board **) b2) - BoardScore(*(Board **) b1);
}

int main()
{
   Trie *trie = TrieScanWordCode(stdin, &WordScore);
   BoardSolver *bs = BoardSolverInit(trie, TRIMMED_ALPHABET);
   Board *pop[POP_SIZE];
   int i, j, mom, dad, gen, best = 0;
   
   srand(time(NULL));
   
   for (i = 0; i < POP_SIZE; i++) {
      pop[i] = BoardRandom(bs);
   }
   
   for (gen = 0; gen < GENERATIONS; gen++) {
      
      qsort(pop, POP_SIZE, sizeof(Board *), compareBoards);
      
      if (BoardScore(pop[0]) > best) {
         best = BoardScore(pop[0]);
         BoardPrintWithStats(stdout, pop[0]);
      }
      
      i = 0;
      j = POP_SIZE / 2;
      while (j < POP_SIZE) {
         mom = i++;
         dad = i++;
         BoardRecycle(pop[j]);
         pop[j++] = BoardBreed(bs, pop[mom], pop[dad]);
         BoardRecycle(pop[j]);
         pop[j++] = BoardBreed(bs, pop[mom], pop[dad]);
      }
   }
   
   for (i = 0; i < POP_SIZE; i++) {
      BoardRecycle(pop[i]);
   }
   
   BoardGarbageCollect();
   TrieDestroy(trie);
   BoardSolverDestroy(bs);
   
   return 0;
}
