#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "Board.h"

int main(int argc, char **argv)
{
   Board *board;
   FILE *in = stdin;
   Trie *trie;
   BoardSolver *bs;
   
   int c;
   char *letters = NULL;
   char *lexFile = NULL;
   
   srand(time(NULL));
   
   opterr = 0;
   
   while ((c = getopt(argc, argv, "b:l:")) != -1) {
      switch (c) {
         case 'b':
            letters = optarg;
            break;
         case 'l':
            lexFile = optarg;
            break;
         case '?':
            if (optopt == 'c')
               fprintf(stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint(optopt))
               fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else
               fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
            return 1;
         default:
            abort();
      }
   }
   
   if (lexFile)
      in = fopen(lexFile, "r");
   
   trie = TrieScanWordCode(in, &WordScore);
   bs = BoardSolverInit(trie);
   
   if (letters)
      board = BoardFromLetters(bs, letters);
   else
      board = BoardRandom(bs);
   
   BoardPrintWithStats(board);
   
   TrieDestroy(trie);
   BoardSolverDestroy(bs);
   
   return 0;
}
