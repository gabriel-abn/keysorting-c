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

char *CriarString(char *str);
Lista *CriarLista(char *nome, Lista *prox);
void LiberarLista(Lista *nomes);
int QuantidadeArquivos(Lista *nomes);
void InverterLista(Lista *nomes);
void ImprimeNomes(Lista *nomes);
int MenorChave(Funcionario *array[], int size);
void SalvarArquivoDeSaida(FILE *saida, int indice, Funcionario *item);
void SelecaoNatural(FILE *arq, Lista *nomesArquivos, int elementosPorParticao, int qtdFuncionarios, int tamReservatorio);

#endif