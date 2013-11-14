#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "Board.h"
#include "Trie.h"

int main(int argc, char **argv)
{
   int flag;
   
   char *letters = NULL;
   FILE *wordCodeStream = stdin;
   
   Board *board;
   Trie *trie;
   BoardSolver *bs;
   
   while ((flag = getopt(argc, argv, "l:c:")) != -1) {
      switch (flag) {
         case 'l':
            letters = optarg;
            break;
         case 'c':
            wordCodeStream = fopen(optarg, "r");
            if (wordCodeStream == NULL) {
               fprintf (stderr, "Unable to open word code file \"%s\"\n", optarg);
            }
            break;
         case '?':
            if (isprint (optopt)) {
               fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            } else {
               fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
            }
      }
   }
   
   trie = TrieScanWordCode(wordCodeStream, &WordScore);
   bs = BoardSolverInit(trie);
   
   if (letters == NULL) {
      srand(time(NULL));
      board = BoardRandom(bs);
   } else {
      board = BoardFromLetters(bs, letters);
   }
   
   BoardPrint(stdout, board);
   printf("Words: %d\nScore: %d\n", BoardWordCount(board), BoardScore(board));
   
   BoardRecycle(board);
   BoardGarbageCollect();
   TrieDestroy(trie);
   BoardSolverDestroy(bs);
   
   if (wordCodeStream != NULL) {
      fclose(wordCodeStream);
   }
   
   return 0;
}
