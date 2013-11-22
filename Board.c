#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Board.h"
#include "PointTree.h"

struct Board
{
   char letters[ROWS][COLS];
   int wordCount;
   int score;
   unsigned long id;
   Board *next;
};

struct BoardSolver
{
   Trie *node;
   PointTree *visited;
   char *alphabet;
   int alphabetSize;
};

static Board *freeList = NULL;

static Board *newBoard()
{
   Board *new;
   
   if (freeList) {
      new = freeList;
      freeList = new->next;
   } else {
      new = malloc(sizeof(Board));
   }
   new->score = 0;
   new->wordCount = 0;
   
   return new;
}

static void freeBoard(Board *b)
{
   b->next = freeList;
   freeList = b;
}

int WordScore(int wordLength)
{
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

BoardSolver *BoardSolverInit(Trie *trie, char *alphabet)
{
   BoardSolver *bs = malloc(sizeof(BoardSolver));
   
   bs->node = trie;
   bs->visited = PointTreeInit();
   bs->alphabetSize = strlen(alphabet);
   bs->alphabet = malloc(bs->alphabetSize + 1);
   strcpy(bs->alphabet, alphabet);
   
   return bs;
}

void BoardSolverDestroy(BoardSolver *bs)
{
   PointTreeRecycle(bs->visited);
   PointTreeGarbageCollect();
   free(bs->alphabet);
   free(bs);
}

Board *BoardRandom(BoardSolver *bs)
{
   char letters[ROWS * COLS];
   int i = 0;
   
   while (i < ROWS * COLS)
      letters[i++] = bs->alphabet[rand() % bs->alphabetSize];
   
   return BoardFromLetters(bs, letters);
}

Board *BoardFromLetters(BoardSolver *bs, char *letters)
{
   static unsigned long id = 1;
   int row, col;
   Board *b = newBoard();
   
   for (row = 0; row < ROWS; row++)
      for (col = 0; col < COLS; col++)
         b->letters[row][col] = letters[row * COLS + col];
   
   b->id = id++;
   solveBoard(b, bs);
   return b;
}

Board *BoardMutate(BoardSolver *bs, Board *board)
{
   int row, col, i = 0;
   char letters[ROWS * COLS];
   
   for (row = 0; row < ROWS; row++) {
      for (col = 0; col < COLS; col++) {
         if (rand() % (ROWS * COLS) == 0) {
            letters[i++] = bs->alphabet[rand() % bs->alphabetSize];
         } else {
            letters[i++] = board->letters[row][col];
         }
      }
   }
   
   return BoardFromLetters(bs, letters);
}

Board *BoardCopy(Board *board)
{
   Board *copy = newBoard();
   memcpy(copy, board, sizeof(Board));
   return copy;
}

void BoardPrint(FILE *stream, Board *board)
{
   int row, col;
   
   for (row = 0; row < ROWS; row++) {
      for (col = 0; col < COLS; col++) {
         fprintf(stream, "%c ", board->letters[row][col]);
      }
      fprintf(stream, "\n");
   }
}

void BoardPrintWithStats(FILE *stream, Board *board)
{
   BoardPrint(stream, board);
   fprintf(stream, "Words: %d\nScore: %d\n", board->wordCount, board->score);
}

int BoardWordCount(Board *board)
{
   return board->wordCount;
}

int BoardScore(Board *board)
{
   return board->score;
}

void BoardRecycle(Board *board)
{
   freeBoard(board);
}

void BoardGarbageCollect()
{
   Board *temp;
   
   while (freeList) {
      temp = freeList->next;
      free(freeList);
      freeList = temp;
   }
}
