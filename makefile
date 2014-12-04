CC = gcc
CFLAGS = -O3 -Wall -Werror -pedantic
OBJS = Board.o Trie.o PointTree.o
EXES = MassSolver WordListEncoder Solver SimAn GenAlg

all: $(EXES)

GenAlg: GenAlg.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o GenAlg

SimAn: SimAn.c $(OBJS)
	$(CC) $(CFLAGS) $^ -lm -o SimAn

Solver: Solver.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o Solver

WordListEncoder: WordListEncoder.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o WordListEncoder

MassSolver: MassSolver.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o MassSolver

clean:
	rm *.o $(EXES)
	
again: clean all
