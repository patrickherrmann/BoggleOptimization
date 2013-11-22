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

%.o: %.c
	$(CC) $(OPTS) -c $<

clean:
	rm *.o MassSolver WordListEncoder Solver SimAn
	
again: clean all
