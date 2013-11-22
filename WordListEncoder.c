#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include "Trie.h"
#include "Board.h"

int main(int argc, char **argv)
{
   int flag, encode = 1;
   while ((flag = getopt(argc, argv, "d")) != -1) {
      switch (flag) {
         case 'd':
            encode = 0;
            break;
         case 'e':
            encode = 1;
            break;
         case '?':
            if (isprint (optopt)) {
               fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            } else {
               fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
            }
      }
   }
   if (encode) {
      TriePrintWordCode(stdout, TrieScanWordList(stdin));
   } else {
      TriePrintWordList(stdout, TrieScanWordCode(stdin, &WordScore));
   }
   
   return 0;
}
