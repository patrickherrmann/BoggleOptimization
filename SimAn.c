#include <stdlib.h>
#include <stdio.h>
#include "SimAn.h"

void SimAnAdvance(SimAn *simAn)
{
   void *neighbor = simAn->neighbor(simAn->state, simAn->neighborConfig);
   int diff = simAn->score(neighbor) - simAn->score(simAn->state);
   
   if (diff >= 0 || (rand() % -diff) < 5) {
      simAn->destroy(simAn->state);
      simAn->state = neighbor;
   } else {
      simAn->destroy(neighbor);
   }
}
