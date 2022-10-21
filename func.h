#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXTAM 2

typedef struct{
    int matricula;
    char nome[50];
}Pessoa;

typedef struct TipoFuncionario
{
  int codigo;
  char nome[50];
  char cpf[15];
  char data_nascimento[11];
  float salario;
} Funcionario;

typedef struct key_sorting
{
  int cod;
  long RRN;
} TKeySorting;

void ImprimirFuncionario(Funcionario *func);
void SalvarEmArquivo(Funcionario *func, FILE *arq);
Funcionario *RecuperarFuncionario(FILE *in);
void CriarBaseDeDados(FILE *arq, int qtdFunc, int *codigos);
Funcionario *BuscaSequencial(int cod, FILE *arq, int tam_arq);
void OrdenarArrayKeySorting(TKeySorting *array, int qtd_func);
void KeySorting(FILE *arq, FILE *arq_ordenado, int qtd_func);
void InsertionSort(int *array, int qtd_func);
Funcionario *BuscaBinaria(int cod, int qtd_func, FILE *arquivo);

#endif