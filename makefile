all: MassSolver

MassSolver: MassSolver.c Board.o WordHashTable.o PointTree.o Trie.o
	gcc MassSolver.c Board.o WordHashTable.o PointTree.o Trie.o -o MassSolver

Board.o: Board.c Board.h
	gcc -c Board.c

WordHashTable.o: WordHashTable.c WordHashTable.h
	gcc -c WordHashTable.c

PointTree.o: PointTree.c PointTree.h
	gcc -c PointTree.c

Trie.o: Trie.c Trie.h
	gcc -c Trie.c
