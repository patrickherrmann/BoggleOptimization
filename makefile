CC = gcc
OPTS = -O3 -Wall -Werror -pedantic

OBJS = Board.o Trie.o PointTree.o

all: MassSolver WordListEncoder Solver SimAn

SimAn: SimAn.c $(OBJS)
	$(CC) $(OPTS) $^ -lm -o SimAn

Solver: Solver.c $(OBJS)
	$(CC) $(OPTS) $^ -o Solver

WordListEncoder: WordListEncoder.c $(OBJS)
	$(CC) $(OPTS) $^ -o WordListEncoder

MassSolver: MassSolver.c $(OBJS)
	$(CC) $(OPTS) $^ -o MassSolver

Board.o: Board.h Board.c
	$(CC) $(OPTS) -c Board.c

Trie.o: Trie.h Trie.c
	$(CC) $(OPTS) -c Trie.c

PointTree.o: PointTree.h PointTree.c
	$(CC) $(OPTS) -c PointTree.c
	
clean:
	rm *.o MassSolver WordListEncoder Solver SimAn
	
again: clean all
