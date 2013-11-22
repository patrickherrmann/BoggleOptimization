CC = gcc
OPTS = -O3 -Wall -Werror -pedantic

MASS_SOLVER_DEPS = Board.o PointTree.o Trie.o
WORD_LIST_ENCODER_DEPS = Trie.o Board.o PointTree.o
SOLVER_DEPS = Board.o PointTree.o Trie.o
SIM_AN_DEPS = Board.o PointTree.o Trie.o

all: MassSolver WordListEncoder Solver SimAn

SimAn: SimAn.c $(SIM_AN_DEPS)
	$(CC) $(OTPS) $? -lm -o SimAn

Solver: Solver.c $(SOLVER_DEPS)
	$(CC) $(OTPS) $? -o Solver

WordListEncoder: WordListEncoder.c $(WORD_LIST_ENCODER_DEPS)
	$(CC) $(OPTS) $? -o WordListEncoder

MassSolver: MassSolver.c $(MASS_SOLVER_DEPS)
	$(CC) $(OPTS) $? -o MassSolver

%.o: %.c
	$(CC) $(OPTS) -c $<
	
clean:
	rm *.o MassSolver WordListEncoder Solver SimAn
	
again: clean all
