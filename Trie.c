#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Trie.h"

#define MAX_WORD_IN 50

void addString(Trie *node, char *string)
{
   int i = 0, childExists = 0;
   char letter;
   Trie *child;
   
   if (*string) {
      letter = tolower(*string);
      while (!childExists && i < node->childCount) {
         child = node->children + i++;
         if (child->letter == letter)
            childExists = 1;
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

Trie *TrieScanWordList(FILE *in)
{
   char word[MAX_WORD_IN];
   Trie *root = calloc(sizeof(Trie), 1);
   root->letter = '~';
   
   while (fscanf(in, "%s", word) != EOF)
      addString(root, word);
   
   return root;
}

void readCode(FILE *in, Trie *node, int level, int (*wordScore)(int))
{
   char letter, childCount;
   int i;
   
   fscanf(in, "%c%c", &letter, &childCount);
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
      readCode(in, node->children + i, level + 1, wordScore);
}

Trie *TrieScanWordCode(FILE *in, int (*wordScore)(int))
{
   Trie *root = calloc(sizeof(Trie), 1);
   readCode(in, root, 0, wordScore);
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

void printAsCharacters(char letter, char childCount)
{
   printf("%c%c", letter, '@' + childCount);
}

void encode(Trie *trie, void (*sink)(char, char))
{
   int i;
   char letter = trie->letter;
   
   if (trie->terminates)
      letter = toupper(letter);
   
   sink(letter, trie->childCount);
   
   for (i = 0; i < trie->childCount; i++)
      encode(trie->children + i, sink);
}

void TriePrintWordCode(Trie *trie)
{
   encode(trie, &printAsCharacters);
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
