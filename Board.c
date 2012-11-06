#include <stdlib.h>
#include <stdio.h>
#include "Board.h"
#include "WordHashTable.h"
#include "PointTree.h"

struct Board {
   char letters[ROWS][COLS];
   int wordCount;
   int score;
};

struct BoardSolver {
   Trie *node;
   WordHashTable *found;
   PointTree *visited;
   int row;
   int col;
};

int WordScore(int wordLength) {
   switch (wordLength) {
      case 0:
      case 1:
      case 2: return 0;
      case 3: 
      case 4: return 1;
      case 5: return 2;
      case 6: return 3;
      case 7: return 5;
      default: return 11;
   }
}

void solveBoard(Board *b, BoardSolver bs)
{
   b->score = 99;
   b->wordCount = 42;
}

BoardSolver *BoardSolverInit(Trie *trie, int wordCapacity)
{
   BoardSolver *bs = malloc(sizeof(BoardSolver));
   
   bs->node = trie;
   bs->found = WordHashTableInit(wordCapacity);
   bs->visited = PointTreeInit();
   
   return bs;
}

void BoardSolverDestroy(BoardSolver *bs)
{
   WordHashTableDestroy(bs->found);
   PointTreeDestroy(bs->visited);
   free(bs);
}

Board *BoardRandom(BoardSolver *bs)
{
   char letters[ROWS * COLS];
   int i = 0;
   
   while (i < ROWS * COLS)
      letters[i++] = 'a' + rand() % 26;
   
   return BoardFromLetters(bs, letters);
}

Board *BoardScan(BoardSolver *bs)
{
   char letters[ROWS * COLS];
   scanf("%s", letters);
   return BoardFromLetters(bs, letters);
}

Board *BoardFromLetters(BoardSolver *bs, char *letters)
{
   int row, col;
   Board *b = malloc(sizeof(Board));
   
   for (row = 0; row < ROWS; row++)
      for (col = 0; col < COLS; col++)
         b->letters[row][col] = letters[row * COLS + col];
   
   solveBoard(b, *bs);
}

void BoardPrint(Board *board)
{
   int row, col;
   
   for (row = 0; row < ROWS; row++) {
      for (col = 0; col < COLS; col++) {
         printf("%c ", board->letters[row][col]);
      }
      printf("\n");
   }
}

int BoardWordCount(Board *board)
{
   return board->wordCount;
}

int BoardScore(Board *board)
{
   return board->score;
}
