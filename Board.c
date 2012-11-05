#include <stdlib.h>
#include "Board.h"

struct Board {
   char letters[ROWS][COLS];
   int score;
};

Board *BoardRandom()
{
   int row, col;
   Board *b = malloc(sizeof(Board));
   for (row = 0; row < ROWS; row++)
      for (col = 0; col < COLS; col++)
         b->letters[row][col] = 'a' + rand() % 26;
   //calculateScore(b, words);
   return b;
}

Board *BoardScan()
{

}

Board *BoardFromLetters(char *letters)
{

}

void BoardPrint(Board *board)
{

}

int BoardScore(Board *board)
{

}
