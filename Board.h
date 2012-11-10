#include "Trie.h"

#define ROWS 4
#define COLS 4

typedef struct Board Board;

typedef struct BoardSolver BoardSolver;

int WordScore(int wordLength);

BoardSolver *BoardSolverInit(Trie *trie);

void BoardSolverDestroy(BoardSolver *bs);

Board *BoardRandom(BoardSolver *bs);

Board *BoardScan(BoardSolver *bs);

Board *BoardFromLetters(BoardSolver *bs, char *letters);

void BoardPrint(Board *board);

int BoardWordCount(Board *board);

int BoardScore(Board *board);
