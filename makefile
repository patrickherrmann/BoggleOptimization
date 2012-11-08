CC = gcc
OPTS = -O3

MASS_SOLVER_DEPS = Board.o WordHashTable.o PointTree.o Trie.o

all: MassSolver

MassSolver: MassSolver.c $(MASS_SOLVER_DEPS)
	$(CC) $(OPTS) $? -o MassSolver

%.o: %.c
	$(CC) $(OPTS) -c $<
	
clean:
	rm *.o MassSolver
	
again: clean all
