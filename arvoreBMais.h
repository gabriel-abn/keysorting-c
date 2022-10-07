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
} record;

// Node
typedef struct node
{
  void **pointers;
  int *keys;
  struct node *parent;
  bool is_leaf;
  int num_keys;
  struct node *next;
} node;

int order = ORDER;
node *queue = NULL;
bool verbose_output = false;

// Enqueue
void enqueue(node *new_node);

// Dequeue
node *dequeue(void);
int height(node *const root);
int pathToLeaves(node *const root, node *child);
void printLeaves(node *const root);
void printTree(node *const root);
void findAndPrint(node *const root, int key, bool verbose);
void findAndPrintRange(node *const root, int range1, int range2, bool verbose);
int findRange(node *const root, int key_start, int key_end, bool verbose, int returned_keys[], void *returned_pointers[]);
node *findLeaf(node *const root, int key, bool verbose);
Funcionario *find(node *root, int key, bool verbose, node **leaf_out);
int cut(int length);

Funcionario *makeRecord(int value);
node *makeNode(void);
node *makeLeaf(void);
int getLeftIndex(node *parent, node *left);
node *insertIntoLeaf(node *leaf, int key, Funcionario *pointer);
node *insertIntoLeafAfterSplitting(node *root, node *leaf, int key, Funcionario *pointer);
node *insertIntoNode(node *root, node *parent, int left_index, int key, node *right);
node *insertIntoNodeAfterSplitting(node *root, node *parent, int left_index, int key, node *right);
node *insertIntoParent(node *root, node *left, int key, node *right);
node *insertIntoNewRoot(node *left, int key, node *right);
node *startNewTree(int key, Funcionario *pointer);
node *insert(node *root, int key, int value);