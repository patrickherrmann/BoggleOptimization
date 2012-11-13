CC = gcc
OPTS = -O3

MASS_SOLVER_DEPS = Board.o PointTree.o Trie.o
WORD_LIST_ENCODER_DEPS = Trie.o
SINGLE_SOLVER_DEPS = Board.o PointTree.o Trie.o
BOG_SIM_AN_DEPS = SimAn.o Board.o PointTree.o Trie.o

all: MassSolver WordListEncoder SingleSolver BogSimAn

BogSimAn: BogSimAn.c $(BOG_SIM_AN_DEPS)
	$(CC) $(OTPS) $? -o BogSimAn

SingleSolver: SingleSolver.c $(SINGLE_SOLVER_DEPS)
	$(CC) $(OTPS) $? -o SingleSolver

WordListEncoder: WordListEncoder.c $(WORD_LIST_ENCODER_DEPS)
	$(CC) $(OPTS) $? -o WordListEncoder

MassSolver: MassSolver.c $(MASS_SOLVER_DEPS)
	$(CC) $(OPTS) $? -o MassSolver

%.o: %.c
	$(CC) $(OPTS) -c $<
	
clean:
	rm *.o MassSolver WordListEncoder SingleSolver BogSimAn
	
again: clean all
