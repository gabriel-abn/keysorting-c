#ifndef SELECAO_NATURAL_H
#define SELECAO_NATURAL_H

#include <stdio.h>
#include <stdlib.h>
#include "func.h"

typedef struct Lista
{
  char *nome;
  struct Lista *prox;
} Lista;

// /*imprime lista de nomes*/
// void imprime(Lista *nomes);

// /*aloca copia de str*/
// char *cria_str(char *str);

// /*cria lista encadeada de nomes. Lembrar de chamar libera_nomes(nomes)*/
// Lista *cria(char *nome, Lista *prox);

// /*desaloca lista encadeada de nomes*/
// void libera(Lista *nomes);

// /*retorna quantidade de nomes*/
// int conta(Lista *nomes);

// /*inverte lista encadeada de nomes*/
// void inverte(Lista *nomes);

char *cria_str(char *str);
Lista *cria(char *nome, Lista *prox);
void libera(Lista *nomes);
int conta(Lista *nomes);
void inverte(Lista *nomes);
void imprime(Lista *nomes);
int menorChave(Funcionario *array[], int size);
void salva_ArqSaida(FILE *saida, int indice, Funcionario *item);
void selecao_natural(FILE *arq, Lista *nome_arquivos_saida, int M, int nFunc, int n);

#endif