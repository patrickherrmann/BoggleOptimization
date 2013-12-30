#ifndef BOARD_H
#define BOARD_H

#include "Trie.h"

#define ROWS 4
#define COLS 4
#define DEFAULT_ALPHABET "abcdefghijklmnopqrstuvwxyz"
#define MUTATION_RATE 0.1

typedef struct Board Board;

typedef struct BoardSolver BoardSolver;

int WordScore(int wordLength);

BoardSolver *BoardSolverInit(Trie *trie, char *alphabet);

void BoardSolverDestroy(BoardSolver *bs);

Board *BoardRandom(BoardSolver *bs);

Board *BoardFromLetters(BoardSolver *bs, char *letters);

Board *BoardMutate(BoardSolver *bs, Board *board);

Board *BoardBreed(BoardSolver *bs, Board *mom, Board *dad);

Board *BoardCopy(Board *board);

void BoardPrint(FILE *stream, Board *board);

void BoardPrintWithStats(FILE *stream, Board *board);

void BoardPrintFoundWords(FILE *stream, Board *board, Trie *trie);

int BoardWordCount(Board *board);

int BoardScore(Board *board);

void BoardRecycle(Board *board);

void BoardGarbageCollect();

#endif
