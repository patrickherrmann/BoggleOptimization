#define ROWS 4
#define COLS 4

typedef struct Board Board;

Board *BoardRandom();

Board *BoardScan();

Board *BoardFromLetters(char *letters);

void BoardPrint(Board *board);

int BoardScore(Board *board);
