#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"

NoArvoreB *createNode(int val, NoArvoreB *child)
{
  NoArvoreB *newNode;
  newNode = (NoArvoreB *)malloc(sizeof(NoArvoreB));
  newNode->val[1] = val;
  newNode->count = 1;
  newNode->link[0] = raiz;
  newNode->link[1] = child;
  return newNode;
}

// Insert node
void insertNode(int val, int pos, NoArvoreB *node, NoArvoreB *child)
{
  int j = node->count;
  while (j > pos)
  {
    node->val[j + 1] = node->val[j];
    node->link[j + 1] = node->link[j];
    j--;
  }
  node->val[j + 1] = val;
  node->link[j + 1] = child;
  node->count++;
}

// Split node
void splitNode(int val, int *pval, int pos, NoArvoreB *node, NoArvoreB *child, NoArvoreB **newNode)
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
    (*newNode)->val[j - median] = node->val[j];
    (*newNode)->link[j - median] = node->link[j];
    j++;
  }
  node->count = median;
  (*newNode)->count = MAX - median;

  if (pos <= MIN)
  {
    insertNode(val, pos, node, child);
  }
  else
  {
    insertNode(val, pos - median, *newNode, child);
  }
  *pval = node->val[node->count];
  (*newNode)->link[0] = node->link[node->count];
  node->count--;
}

// Set the value
int setValue(int val, int *pval, NoArvoreB *node, NoArvoreB **child)
{
  int pos;

  if (!node)
  {
    *pval = val;
    *child = NULL;
    return 1;
  }

  if (val < node->val[1])
  {
    pos = 0;
  }
  else
  {
    for (pos = node->count; (val < node->val[pos] && pos > 1); pos--)
      ;
    if (val == node->val[pos])
    {
      printf("Duplicates are not permitted\n");
      return 0;
    }
  }
  if (setValue(val, pval, node->link[pos], child))
  {
    if (node->count < MAX)
    {
      insertNode(*pval, pos, node, *child);
    }
    else
    {
      splitNode(*pval, pval, pos, node, *child, child);
      return 1;
    }
  }
  return 0;
}

// Insert the value
void insert(int val)
{
  int flag, i;
  NoArvoreB *child;

  flag = setValue(val, &i, raiz, &child);
  if (flag)
  {
    raiz = createNode(i, child);
  }
}

// Search node
void search(int val, int *pos, NoArvoreB *myNode)
{
  if (!myNode)
  {
    return;
  }

  if (val < myNode->val[1])
  {
    *pos = 0;
  }
  else
  {
    for (*pos = myNode->count;
         (val < myNode->val[*pos] && *pos > 1); (*pos)--)
      ;
    if (val == myNode->val[*pos])
    {
      printf("%d is found", val);
      return;
    }
  }
  search(val, pos, myNode->link[*pos]);

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
      traversal(myNode->link[i]);
      printf("%d ", myNode->val[i + 1]);
    }
    traversal(myNode->link[i]);
  }
}
