#ifndef POINT_TREE_H
#define POINT_TREE_H

typedef struct PointTree PointTree;

PointTree *PointTreeInit();

void PointTreeRecycle(PointTree *tree);

void PointTreeGarbageCollect();

void PointTreeAdd(PointTree **tree, int row, int col);

int PointTreePathContains(PointTree *tree, int row, int col);

#endif
