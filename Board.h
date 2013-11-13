#ifndef BOARD_H
#define BOARD_H

#include "Trie.h"

#define ROWS 4
#define COLS 4

typedef struct Board Board;

typedef struct BoardSolver BoardSolver;

int WordScore(int wordLength);

BoardSolver *BoardSolverInit(Trie *trie);

void BoardSolverDestroy(BoardSolver *bs);

Board *BoardRandom(BoardSolver *bs);

Board *BoardFromLetters(BoardSolver *bs, char *letters);

Board *BoardMutate(BoardSolver *bs, Board *board);

Board *BoardCopy(Board *board);

void BoardPrint(FILE *stream, Board *board);

void BoardPrintWithStats(FILE *stream, Board *board);

int BoardWordCount(Board *board);

int BoardScore(Board *board);

void BoardRecycle(Board *board);

void BoardDestroyAll();

#endif
