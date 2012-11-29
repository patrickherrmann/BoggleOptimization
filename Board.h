#include "Trie.h"

#define ROWS 5
#define COLS 5

typedef struct Board Board;

typedef struct BoardSolver BoardSolver;

int WordScore(int wordLength);

BoardSolver *BoardSolverInit(Trie *trie);

void BoardSolverDestroy(BoardSolver *bs);

Board *BoardRandom(BoardSolver *bs);

Board *BoardScan(BoardSolver *bs);

Board *BoardFromLetters(BoardSolver *bs, char *letters);

Board *BoardMutate(BoardSolver *bs, Board *board);

Board *BoardCopy(Board *board);

void BoardPrint(Board *board);

void BoardPrintWithStats(Board *board);

int BoardWordCount(Board *board);

int BoardScore(Board *board);

void BoardRecycle(Board *board);

void BoardDestroyAll();
