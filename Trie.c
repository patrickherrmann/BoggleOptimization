#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Trie.h"

#define MAX_WORD_STDIN 20

void addString(Trie *node, char *string)
{
   int i = 0, childExists = 0;
   char letter;
   Trie *child;
   
   if (*string) {
      letter = tolower(*string);
      while (!childExists && i < node->childCount) {
         child = node->children + i++;
         if (child->letter == letter) {
            childExists = 1;
         }
      }
      if (!childExists) {
         node->children = 
            realloc(node->children, sizeof(Trie) * (node->childCount + 1));
         child = node->children + node->childCount++;
         child->letter = letter;
         child->childCount = 0;
         child->children = NULL;
      }
      addString(child, string + 1);
   } else {
      node->terminates = 1;
   }
}

Trie *TrieScanWordList()
{
   char in[MAX_WORD_STDIN];
   Trie *root = calloc(sizeof(Trie), 1);
   root->letter = '~';
   
   while (scanf("%s", in) != EOF)
      addString(root, in);
   
   return root;
}

void readCode(Trie *node, int level, int (*wordScore)(int))
{
   char letter, childCount;
   int i;
   
   scanf("%c%c", &letter, &childCount);
   childCount -= '@';
   
   if (isupper(letter)) {
      node->terminates = 1;
      letter = tolower(letter);
   }
   
   node->score = wordScore(level);
   node->letter = letter;
   node->childCount = childCount;
   
   if (childCount)
      node->children = calloc(sizeof(Trie), childCount);
   
   for (i = 0; i < childCount; i++)
      readCode(node->children + i, level + 1, wordScore);
}

Trie *TrieScanWordCode(int (*wordScore)(int))
{
   Trie *root = calloc(sizeof(Trie), 1);
   readCode(root, 0, wordScore);
   return root;
}

void printString(Trie *node, char *prefix)
{
   int prefixLen = strlen(prefix), i;
   char *fragment = malloc(prefixLen + 2);
   
   strcpy(fragment, prefix);
   fragment[prefixLen] = node->letter;
   fragment[prefixLen + 1] = '\0';
   
   if (node->terminates)
      printf("%s\n", fragment + 1);
   
   for (i = 0; i < node->childCount; i++)
      printString(node->children + i, fragment);
   
   free(fragment);
}

void TriePrintWordList(Trie *trie)
{
   printString(trie, "");
}

void TriePrintWordCode(Trie *trie)
{
   int i;
   char letter = trie->letter;
   
   if (trie->terminates)
      letter = toupper(letter);
   
   printf("%c%c", letter, '@' + trie->childCount);
   
   for (i = 0; i < trie->childCount; i++)
      TriePrintWordCode(trie->children + i);
   
   
}

void destroyNode(Trie *node)
{
   int i;
   
   for (i = 0; i < node->childCount; i++)
      destroyNode(node->children + i);
   
   free(node->children);
}

void TrieDestroy(Trie *trie)
{
   destroyNode(trie);
   free(trie);
}

Trie *TrieGetChild(Trie *trie, char letter)
{
   int min, max, mid;
   char childLetter;
   
   min = 0;
   max = trie->childCount - 1;
   
   while (max >= min) {
      mid = (min + max) / 2;
      childLetter = trie->children[mid].letter;
      if (childLetter < letter)
         min = mid + 1;
      else if (childLetter > letter)
         max = mid - 1;
      else
         return trie->children + mid;
   }
   
   return NULL;
}
