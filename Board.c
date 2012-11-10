#include <stdlib.h>
#include <stdio.h>
#include "Board.h"
#include "PointTree.h"

struct Board {
   char letters[ROWS][COLS];
   int wordCount;
   int score;
   unsigned int id;
};

struct BoardSolver {
   Trie *node;
   PointTree *visited;
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

void considerNode(Board *b, BoardSolver bs, int row, int col)
{
   Trie *child;
   
   if (PointTreePathContains(bs.visited, row, col)) return;
   
   child = TrieGetChild(bs.node, b->letters[row][col]);
   
   if (!child) return;
   
   if (child->terminates && child->foundInBoard != b->id) {
      b->score += child->score;
      b->wordCount++;
      child->foundInBoard = b->id;
   }
   
   bs.node = child;
   PointTreeAdd(&bs.visited, row, col);
   
   if (row > 0) {
      if (col > 0)
         considerNode(b, bs, row - 1, col - 1);
      if (col < COLS - 1)
         considerNode(b, bs, row - 1, col + 1);
      considerNode(b, bs, row - 1, col);
   }
   if (row < ROWS - 1) {
      if (col > 0)
         considerNode(b, bs, row + 1, col - 1);
      if (col < COLS - 1)
         considerNode(b, bs, row + 1, col + 1);
      considerNode(b, bs, row + 1, col);
   }
   if (col > 0)
      considerNode(b, bs, row, col - 1);
   if (col < COLS - 1)
      considerNode(b, bs, row, col + 1);
}

void solveBoard(Board *b, BoardSolver *bs)
{
   int row, col;
   
   for (row = 0; row < ROWS; row++)
      for (col = 0; col < COLS; col++)
         considerNode(b, *bs, row, col);
   
   PointTreeRecycle(bs->visited);
   bs->visited = PointTreeInit();
}

BoardSolver *BoardSolverInit(Trie *trie)
{
   BoardSolver *bs = malloc(sizeof(BoardSolver));
   
   bs->node = trie;
   bs->visited = PointTreeInit();
   
   return bs;
}

void BoardSolverDestroy(BoardSolver *bs)
{
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
   static unsigned int id = 1;
   int row, col;
   Board *b = malloc(sizeof(Board));
   
   for (row = 0; row < ROWS; row++)
      for (col = 0; col < COLS; col++)
         b->letters[row][col] = letters[row * COLS + col];
   
   b->id = id++;
   solveBoard(b, bs);
   return b;
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
