#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2

typedef struct no_arvoreB
{
  int valor[MAX + 1];
  int count;
  struct no_arvoreB *prox[MAX + 1];
} NoArvoreB;

NoArvoreB *raiz;

NoArvoreB *criarNo(int val, NoArvoreB *child);
void InserirNo(int val, int pos, NoArvoreB *node, NoArvoreB *child);
void DividirNo(int val, int *pval, int pos, NoArvoreB *node, NoArvoreB *child, NoArvoreB **newNode);
int AtribuirValor(int val, int *pval, NoArvoreB *node, NoArvoreB **child);
void Inserir(int val);
void Procurar(int val, int *pos, NoArvoreB *myNode);
void traversal(NoArvoreB *myNode);
void copySuccessor(NoArvoreB *myNode, int pos);
void rightShift(NoArvoreB *myNode, int pos);
void leftShift(NoArvoreB *myNode, int pos);
void mergeNodes(NoArvoreB *myNode, int pos);
void adjustNode(NoArvoreB *myNode, int pos);