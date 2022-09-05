
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "func.h"

void ImprimirFuncionario(Funcionario *func)
{
  printf("\n\nNome: %s", func->nome);
  printf("\nCPF: %s", func->cpf);
  printf("\nCodigo: %i", func->codigo);
  printf("\nData de nascimento: %s", func->data_nascimento);
  printf("\nSalario: %.2f", func->salario);
  printf("\n");
}

void SalvarEmArquivo(Funcionario *func, FILE *arq)
{
  fwrite(&func->codigo, sizeof(int), 1, arq);
  fwrite(func->nome, sizeof(char), sizeof(func->nome), arq);
  fwrite(func->cpf, sizeof(char), sizeof(func->cpf), arq);
  fwrite(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), arq);
  fwrite(&func->salario, sizeof(float), 1, arq);
}

Funcionario *RecuperarFuncionario(FILE *in)
{
  Funcionario *funcionario = (Funcionario *)malloc(sizeof(Funcionario));

  if (0 >= fread(&funcionario->codigo, sizeof(int), 1, in))
  {
    free(funcionario);
    return NULL;
  }
  fread(funcionario->nome, sizeof(char), sizeof(funcionario->nome), in);
  fread(funcionario->cpf, sizeof(char), sizeof(funcionario->cpf), in);
  fread(funcionario->data_nascimento, sizeof(char), sizeof(funcionario->data_nascimento), in);
  fread(&funcionario->salario, sizeof(float), 1, in);

  return funcionario;
}

void CriarBaseDeDados(FILE *arq, int nFunc, int *cod)
{
  srand(time(NULL));
  for (int i = 1; i <= nFunc; i++)
  {
    Funcionario func;
    func.codigo = cod[i - 1];
    sprintf(func.nome, "Funcionario %i", i);
    sprintf(func.cpf, "%d.%d.%d-%d", rand() % 899 + 100, rand() % 899 + 100, rand() % 899 + 100, rand() % 89 + 10);
    sprintf(func.data_nascimento, "%d/%d/%d", rand() % 29, rand() % 12, rand() % 70 + 1952);
    func.salario = 1000 + nFunc;
    fseek(arq, (i - 1) * sizeof(Funcionario), SEEK_SET);
    SalvarEmArquivo(&func, arq);
  }
}

Funcionario *BuscaBinaria(int codigo, int quantidadeFuncionarios, FILE *arq)
{
  clock_t tempoBinarioComeco, tempoBinarioFim;
  double tempoExecucaoBinario = 0.0;
  int esquerda = 0, direita = quantidadeFuncionarios - 1, middle = 0;
  int quantidadeComparacoes = 0;

  if (codigo > quantidadeFuncionarios)
  {
    printf("Codigo invalido!\n");
    return NULL;
  }
  tempoBinarioComeco = clock();

  while (esquerda <= direita)
  {
    middle = trunc((esquerda + direita) / 2);
    fseek(arq, middle * sizeof(Funcionario), SEEK_SET);
    Funcionario *aux = RecuperarFuncionario(arq);
    quantidadeComparacoes++;
    int codigoComp = (int)aux->codigo;
    if (codigoComp == codigo)
    {
      printf("Numero de comparacoes na busca binaria: %d\n", quantidadeComparacoes);
      tempoBinarioFim = clock();
      tempoExecucaoBinario += (double)(tempoBinarioFim - tempoBinarioComeco) / CLOCKS_PER_SEC;
      printf("Tempo de execucao na busca binaria: %.8f\n", tempoExecucaoBinario);
      return aux;
    }
    else if (codigoComp < codigo)
    {
      esquerda = middle + 1;
    }
    else if (codigoComp > codigo)
    {
      direita = middle - 1;
    }
    else
    {
      printf("ERRO!\n");
    }
  }

  return NULL;
}

Funcionario *BuscaSequencial(int cod, FILE *arq, int tam_arq)
{
  clock_t tempoSequencialComeco, tempoSequencialFim;
  double tempoExecucaoSequencial = 0.0;
  int comparacoes = 0;

  tempoSequencialComeco = clock();

  for (int i = 0; i < tam_arq; i++)
  {
    comparacoes++;
    fseek(arq, i * sizeof(Funcionario), SEEK_SET);
    Funcionario *funcionario = RecuperarFuncionario(arq);
    if (funcionario->codigo == cod)
    {
      printf("Numero de comparacoes na busca sequencial: %d\n", comparacoes);
      tempoSequencialFim = clock();
      tempoExecucaoSequencial += (double)(tempoSequencialFim - tempoSequencialComeco) / CLOCKS_PER_SEC;
      printf("Tempo de execucao na busca sequencial: %.8f\n", tempoExecucaoSequencial);
      return funcionario;
    }
  }

  return NULL;
}

void OrdenarArrayKeySorting(TKeySorting *array, int quantidadeFuncionario)
{

  for (int i = 0; i < quantidadeFuncionario; i++)
  {
    for (int j = i + 1; j < quantidadeFuncionario; j++)
    {
      if (array[i].cod > array[j].cod)
      {
        TKeySorting aux = array[i];
        array[i] = array[j];
        array[j] = aux;
      }
    }
  }
}

void KeySorting(FILE *arq, FILE *arquivoOrdenado, int quantidadeFuncionario)
{

  printf("\nReaizando metodo do Key Sorting ... \n");

  clock_t comecoTime, fimTime;
  double tempoDeExecucao = 0.0;

  comecoTime = clock();

  TKeySorting array[quantidadeFuncionario];

  rewind(arq);

  for (int i = 0; i < quantidadeFuncionario; i++)
  {
    fseek(arq, i * sizeof(Funcionario), SEEK_SET);
    array[i].RRN = ftell(arq);
    Funcionario *func = RecuperarFuncionario(arq);
    array[i].cod = func->codigo;
  }

  OrdenarArrayKeySorting(array, quantidadeFuncionario);

  rewind(arq);

  for (int i = 0; i < quantidadeFuncionario; i++)
  {

    fseek(arq, array[i].RRN, SEEK_SET);
    Funcionario *func = RecuperarFuncionario(arq);

    fseek(arquivoOrdenado, i * sizeof(Funcionario), SEEK_SET);
    SalvarEmArquivo(func, arquivoOrdenado);
  }

  printf("Termino do KeySorting!\n");
  fimTime = clock();
  tempoDeExecucao += (double)(fimTime - comecoTime) / CLOCKS_PER_SEC;
  printf("\nTempo gasto na execucao do Key Sorting: %.8f s\n", tempoDeExecucao);
}
