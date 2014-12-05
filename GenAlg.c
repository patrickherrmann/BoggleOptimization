#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "Board.h"

#define TRIMMED_ALPHABET "acdegilmnoprst"
#define PARAMS_POP_SIZE 8
#define PARAMS_GENS 40
#define MAX_POP_SIZE 4000
#define MAX_SOLVES 50000

struct GenAlgParams {
   int popSize;
   int gens;
   float mutationRate;
   float keepRate;
   int empiricalScore;
};

int compareBoards(const void *b1, const void *b2)
{
   return BoardScore(*(Board **) b2) - BoardScore(*(Board **) b1);
}

int compareParams(const void *p1, const void *p2)
{
   return ((struct GenAlgParams *) p2)->empiricalScore - ((struct GenAlgParams *) p1)->empiricalScore;
}

int performAlgorithm(BoardSolver *bs, struct GenAlgParams *params, int verbose)
{
   int i, j, gen, best = 0;
   int threshold = params->popSize * params->keepRate;

   Board **pop = malloc(sizeof(Board *) * params->popSize);

   for (i = 0; i < params->popSize; i++) {
      pop[i] = BoardRandom(bs);
   }
   
   for (gen = 0; gen < params->gens; gen++) {
      
      qsort(pop, params->popSize, sizeof(Board *), compareBoards);
      
      if (BoardScore(pop[0]) > best) {
         best = BoardScore(pop[0]);
         if (verbose) {
            BoardPrintWithStats(stdout, pop[0]);
         }
      }
      
      i = 0;
      j = threshold;
      while (j < params->popSize) {
         BoardRecycle(pop[j]);
         pop[j++] = BoardMutate(bs, pop[i++], params->mutationRate);
         /*i %= threshold;*/
      }
   }
   
   for (i = 0; i < params->popSize; i++) {
      BoardRecycle(pop[i]);
   }

   return best;
}

void printParams(struct GenAlgParams *params)
{
   printf("Population:\t%d\n", params->popSize);
   printf("Generations:\t%d\n", params->gens);
   printf("Mutation Rate:\t%0.2f\n", params->mutationRate);
   printf("Keep Rate:\t%0.2f\n", params->keepRate);
}

void printParamsWithScore(struct GenAlgParams *params)
{
   printParams(params);
   printf("Score:\t%d\n", params->empiricalScore);
}

void scoreParams(BoardSolver *bs, struct GenAlgParams *params)
{
   int a = performAlgorithm(bs, params, 0);
   int b = performAlgorithm(bs, params, 0);
   params->empiricalScore = (a + b) / 2;
}

void randomizeParams(struct GenAlgParams *params)
{
   params->popSize = rand() % (MAX_POP_SIZE - 1) + 1;
   params->gens = (MAX_SOLVES * 2) / params->popSize;
   params->mutationRate = ((float) rand() / RAND_MAX) * 0.2;
   params->keepRate = ((float) rand() / RAND_MAX) * 0.5 + 0.1;
}

void mutateParams(struct GenAlgParams *params)
{
   params->popSize += rand() % 100;
   if (params->popSize > MAX_POP_SIZE) {
      params->popSize = MAX_POP_SIZE;
   }
   params->gens = (MAX_SOLVES * 2) / params->popSize;
   params->mutationRate *= ((float) rand() / RAND_MAX) * 0.2 + 0.9;
   params->keepRate *= ((float) rand() / RAND_MAX) * 0.5 + 0.75;
}

void evolveParams(BoardSolver *bs)
{
   struct GenAlgParams *pop[PARAMS_POP_SIZE];
   int i, j, gen, best;

   best = 0;

   for (i = 0; i < PARAMS_POP_SIZE; i++) {
      pop[i] = malloc(sizeof(struct GenAlgParams));
      randomizeParams(pop[i]);
      scoreParams(bs, pop[i]);
   }

   for (gen = 0; gen < PARAMS_GENS; gen++) {
      qsort(pop, PARAMS_POP_SIZE, sizeof(struct GenAlgParams *), compareParams);
      
      if (pop[0]->empiricalScore > best) {
         best = pop[0]->empiricalScore;
         printParamsWithScore(pop[0]);
      }

      i = 0;
      j = PARAMS_POP_SIZE / 2;

      while (j < PARAMS_POP_SIZE) {
         free(pop[j]);
         pop[j] = malloc(sizeof(struct GenAlgParams));
         memcpy(pop[j], pop[i], sizeof(struct GenAlgParams));
         mutateParams(pop[j]);
         scoreParams(bs, pop[j]);
         i++;
         j++;
      }
   }

   for (i = 0; i < PARAMS_POP_SIZE; i++) {
      free(pop[i]);
   }
}

int main(int argc, char *argv[])
{
   Trie *trie = TrieScanWordCode(stdin, &WordScore);
   BoardSolver *bs = BoardSolverInit(trie, TRIMMED_ALPHABET);
   struct GenAlgParams params;
   
   srand(time(NULL));

   if (argc > 1) {
      evolveParams(bs);
      printf("\n");
   } else {
      params.popSize = 2000;
      params.gens = 128;
      params.mutationRate = 0.13;
      params.keepRate = 0.37;

      printParams(&params);
      printf("\n");
      
      performAlgorithm(bs, &params, 1);
   }
   
   BoardGarbageCollect();
   TrieDestroy(trie);
   BoardSolverDestroy(bs);
   
   return 0;
}
