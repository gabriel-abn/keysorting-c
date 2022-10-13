#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

// Default order
#define ORDER 3

typedef struct record
{
  int value;
  Funcionario reg;
} record;

// Node
typedef struct No
{
  void **pointers;
  int *keys;
  struct No *parent;
  bool is_leaf;
  int num_keys;
  struct No *next;
} No;

int order = ORDER;
No *queue = NULL;
bool verbose_output = false;

void enqueue(No *new_node);
No *dequeue(void);
void printLeaves(No *const root);
int height(No *const root);
int pathToLeaves(No *const root, No *child);
void printTree(No *const root);
void findAndPrint(No *const root, int key, bool verbose);
void findAndPrintRange(No *const root, int key_start, int key_end, bool verbose);
int findRange(No *const root, int key_start, int key_end, bool verbose, int returned_keys[], void *returned_pointers[]);
No *findLeaf(No *const root, int key, bool verbose);
record *find(No *root, int key, bool verbose, No **leaf_out);
int cut(int length);
record *makeRecord(int value);
No *makeNode(void);
No *makeLeaf(void);
int getLeftIndex(No *parent, No *left);
No *insertIntoLeaf(No *leaf, int key, record *pointer);
No *insertIntoLeafAfterSplitting(No *root, No *leaf, int key, record *pointer);
No *insertIntoNode(No *root, No *n, int left_index, int key, No *right);
No *insertIntoNodeAfterSplitting(No *root, No *old_node, int left_index, int key, No *right);
No *insertIntoParent(No *root, No *left, int key, No *right);
No *insertIntoNewRoot(No *left, int key, No *right);
No *startNewTree(int key, record *pointer);
No *insert(No *root, int key, int value);