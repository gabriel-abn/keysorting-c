#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2

typedef struct no_arvoreB
{
  int val[MAX + 1], count;
  struct no_arvoreB *link[MAX + 1];
} NoArvoreB;

typedef NoArvoreB *raiz;

NoArvoreB *createNode(int val, NoArvoreB *child);
void insertNode(int val, int pos, NoArvoreB *node, NoArvoreB *child);
void splitNode(int val, int *pval, int pos, NoArvoreB *node, NoArvoreB *child, NoArvoreB **newNode);
int setValue(int val, int *pval, NoArvoreB *node, NoArvoreB **child);
void insert(int val);
void search(int val, int *pos, NoArvoreB *myNode);
void traversal(NoArvoreB *myNode);