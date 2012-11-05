#include <stdlib.h>
#include "PointTree.h"

struct PointTree {
   int row;
   int col;
   PointTree *parent;
   PointTree *sib;
   PointTree *child;
};

static PointTree *freeNodes = NULL;

static void freeNode(PointTree *node)
{
   node->sib = freeNodes;
   freeNodes = node;
}

static PointTree *newNode()
{
   PointTree *new;
   
   if (freeNodes) {
      new = freeNodes;
      freeNodes = new->sib;
   } else {
      new = malloc(sizeof(PointTree));
   }
   
   return new;
}

PointTree *PointTreeInit()
{
   PointTree *root = newNode();
   
   root->row = -1;
   root->col = -1;
   root->parent = NULL;
   root->sib = NULL;
   root->child = NULL;
   
   return root;
}

void PointTreeRecycle(PointTree *tree)
{
   if (tree) {
      PointTreeRecycle(tree->sib);
      PointTreeRecycle(tree->child);
      freeNode(tree);
   }
}

void PointTreeDestroy(PointTree *tree)
{
   PointTree *temp;
   
   PointTreeRecycle(tree);
   while (freeNodes) {
      temp = freeNodes->sib;
      free(freeNodes);
      freeNodes = temp;
   }
}

void PointTreeAdd(PointTree **tree, int row, int col)
{
   PointTree *new = calloc(sizeof(PointTree), 1), *child;
   
   new->parent = *tree;
   new->child = NULL;
   new->row = row;
   new->col = col;
   
   if (!(*tree)->child) {
      (*tree)->child = new;
   } else {
      child = (*tree)->child;
      while (child->sib)
         child = child->sib;
      child->sib = new;
   }
   *tree = new;
}

int PointTreePathContains(PointTree *tree, int row, int col)
{
   int found = 0;
   while (!found && tree) {
      if (tree->row == row && tree->col == col)
         found = 1;
      else
         tree = tree->parent;
   }
   return found;
}
