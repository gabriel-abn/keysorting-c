#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"

NoArvoreB *criarNo(int val, NoArvoreB *child)
{
  NoArvoreB *noAux;
  noAux = (NoArvoreB *)malloc(sizeof(NoArvoreB));
  noAux->valor[1] = val;
  noAux->count = 1;
  noAux->prox[0] = raiz;
  noAux->prox[1] = child;
  return noAux;
}

// Insert node
void InserirNo(int val, int pos, NoArvoreB *node, NoArvoreB *child)
{
  int j = node->count;
  while (j > pos)
  {
    node->valor[j + 1] = node->valor[j];
    node->prox[j + 1] = node->prox[j];
    j--;
  }
  node->valor[j + 1] = val;
  node->prox[j + 1] = child;
  node->count++;
}

// Split node
void DividirNo(int val, int *pval, int pos, NoArvoreB *node, NoArvoreB *child, NoArvoreB **newNode)
{
  int median, j;

  if (pos > MIN)
    median = MIN + 1;
  else
    median = MIN;

  *newNode = (NoArvoreB *)malloc(sizeof(NoArvoreB));
  j = median + 1;
  while (j <= MAX)
  {
    (*newNode)->valor[j - median] = node->valor[j];
    (*newNode)->prox[j - median] = node->prox[j];
    j++;
  }
  node->count = median;
  (*newNode)->count = MAX - median;

  if (pos <= MIN)
  {
    InserirNo(val, pos, node, child);
  }
  else
  {
    InserirNo(val, pos - median, *newNode, child);
  }
  *pval = node->valor[node->count];
  (*newNode)->prox[0] = node->prox[node->count];
  node->count--;
}

// Set the value
int AtribuirValor(int val, int *pval, NoArvoreB *node, NoArvoreB **child)
{
  int pos;

  if (!node)
  {
    *pval = val;
    *child = NULL;
    return 1;
  }

  if (val < node->valor[1])
  {
    pos = 0;
  }
  else
  {
    for (pos = node->count; (val < node->valor[pos] && pos > 1); pos--)
      ;
    if (val == node->valor[pos])
    {
      printf("Duplicates are not permitted\n");
      return 0;
    }
  }
  if (AtribuirValor(val, pval, node->prox[pos], child))
  {
    if (node->count < MAX)
    {
      InserirNo(*pval, pos, node, *child);
    }
    else
    {
      DividirNo(*pval, pval, pos, node, *child, child);
      return 1;
    }
  }
  return 0;
}

// Insert the value
void Inserir(int val)
{
  int flag, i;
  NoArvoreB *child;

  flag = AtribuirValor(val, &i, raiz, &child);
  if (flag)
  {
    raiz = criarNo(i, child);
  }
}

// Search node
void Procurar(int val, int *pos, NoArvoreB *myNode)
{
  if (!myNode)
  {
    return;
  }

  if (val < myNode->valor[1])
  {
    *pos = 0;
  }
  else
  {
    for (*pos = myNode->count;
         (val < myNode->valor[*pos] && *pos > 1); (*pos)--)
      ;
    if (val == myNode->valor[*pos])
    {
      printf("%d is found", val);
      return;
    }
  }
  Procurar(val, pos, myNode->prox[*pos]);

  return;
}

// Traverse then nodes
void traversal(NoArvoreB *myNode)
{
  int i;
  if (myNode)
  {
    for (i = 0; i < myNode->count; i++)
    {
      traversal(myNode->prox[i]);
      printf("%d ", myNode->valor[i + 1]);
    }
    traversal(myNode->prox[i]);
  }
}

// Copy the successor
void copySuccessor(NoArvoreB *myNode, int pos)
{
  NoArvoreB *dummy;
  dummy = myNode->prox[pos];

  for (; dummy->prox[0] != NULL;)
    dummy = dummy->prox[0];
  myNode->valor[pos] = dummy->valor[1];
}

// Do rightshift
void rightShift(NoArvoreB *myNode, int pos)
{
  NoArvoreB *x = myNode->prox[pos];
  int j = x->count;

  while (j > 0)
  {
    x->valor[j + 1] = x->valor[j];
    x->prox[j + 1] = x->prox[j];
  }
  x->valor[1] = myNode->valor[pos];
  x->prox[1] = x->prox[0];
  x->count++;

  x = myNode->prox[pos - 1];
  myNode->valor[pos] = x->valor[x->count];
  myNode->prox[pos] = x->prox[x->count];
  x->count--;
  return;
}

// Do leftshift
void leftShift(NoArvoreB *myNode, int pos)
{
  int j = 1;
  NoArvoreB *x = myNode->prox[pos - 1];

  x->count++;
  x->valor[x->count] = myNode->valor[pos];
  x->prox[x->count] = myNode->prox[pos]->prox[0];

  x = myNode->prox[pos];
  myNode->valor[pos] = x->valor[1];
  x->prox[0] = x->prox[1];
  x->count--;

  while (j <= x->count)
  {
    x->valor[j] = x->valor[j + 1];
    x->prox[j] = x->prox[j + 1];
    j++;
  }
  return;
}

// Merge the nodes
void mergeNodes(NoArvoreB *myNode, int pos)
{
  int j = 1;
  NoArvoreB *x1 = myNode->prox[pos], *x2 = myNode->prox[pos - 1];

  x2->count++;
  x2->valor[x2->count] = myNode->valor[pos];
  x2->prox[x2->count] = myNode->prox[0];

  while (j <= x1->count)
  {
    x2->count++;
    x2->valor[x2->count] = x1->valor[j];
    x2->prox[x2->count] = x1->prox[j];
    j++;
  }

  j = pos;
  while (j < myNode->count)
  {
    myNode->valor[j] = myNode->valor[j + 1];
    myNode->prox[j] = myNode->prox[j + 1];
    j++;
  }
  myNode->count--;
  free(x1);
}

// Adjust the node
void adjustNode(NoArvoreB *myNode, int pos)
{
  if (!pos)
  {
    if (myNode->prox[1]->count > MIN)
    {
      leftShift(myNode, 1);
    }
    else
    {
      mergeNodes(myNode, 1);
    }
  }
  else
  {
    if (myNode->count != pos)
    {
      if (myNode->prox[pos - 1]->count > MIN)
      {
        rightShift(myNode, pos);
      }
      else
      {
        if (myNode->prox[pos + 1]->count > MIN)
        {
          leftShift(myNode, pos + 1);
        }
        else
        {
          mergeNodes(myNode, pos);
        }
      }
    }
    else
    {
      if (myNode->prox[pos - 1]->count > MIN)
        rightShift(myNode, pos);
      else
        mergeNodes(myNode, pos);
    }
  }
}
