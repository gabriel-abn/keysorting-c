#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "selecao-natural.h"
#include "func.h"

char *CriarString(char *str)
{
  char *s = (char *)calloc(strlen(str) + 1, sizeof(char));
  strcpy(s, str);
  return s;
}

Lista *CriarLista(char *nome, Lista *prox)
{
  Lista *nomes = (Lista *)malloc(sizeof(Lista));
  nomes->nome = nome;
  nomes->prox = prox;
  return nomes;
}

void LiberarLista(Lista *nomes)
{
  Lista *temp = NULL;
  while (nomes)
  {
    temp = nomes->prox;
    free(nomes->nome);
    free(nomes);
    nomes = temp;
  }
}

int QuantidadeArquivos(Lista *nomes)
{
  int qtd = 0;
  while (nomes)
  {
    qtd += 1;
    nomes = nomes->prox;
  }
  return qtd;
}

void InverterLista(Lista *nomes)
{
  int i;
  int qtd = QuantidadeArquivos(nomes);
  Lista *atual = nomes;
  Lista **temp = (Lista **)malloc(sizeof(Lista *) * (qtd + 1));
  temp[qtd] = NULL;
  for (i = qtd - 1; i >= 0; i--)
  {
    temp[i] = atual;
    atual = atual->prox;
  }
  for (i = 0; i < qtd; i++)
  {
    temp[i]->prox = temp[i + 1];
  }
}

void ImprimeNomes(Lista *nomes)
{
  while (nomes)
  {
    printf("| %s ", nomes->nome);
    nomes = nomes->prox;
  }
  printf("\n\n");
}

int MenorChave(Funcionario *array[], int size)
{
  int posMenor, i, posNotNULL;
  char posNull = 'N';
  Funcionario *menor;

  for (i = 0; i < size; i++)
  {
    if (array[i] == NULL)
    {
      posNull = 'S';
    }
    else
    {
      posNotNULL = i;
    }
  }
  if (posNull == 'N')
  {
    for (i = 0; i < size; i++)
    {
      if (i == 0)
      {
        menor = array[0];
        posMenor = 0;
      }
      else if (menor->codigo > array[i]->codigo)
      {
        menor = array[i];
        posMenor = i;
      }
    }
  }
  else
  {
    return posNotNULL;
  }

  return posMenor;
}

void SalvarArquivoDeSaida(FILE *saida, int indice, Funcionario *item)
{
  fseek(saida, (indice) * sizeof(Funcionario), SEEK_SET);
  SalvarEmArquivo(item, saida);
}

void SelecaoNatural(FILE *arq, Lista *nomesArquivos, int elementosPorParticao, int qtdFuncionarios, int tamReservatorio)
{
  rewind(arq);

  Funcionario *array[elementosPorParticao], *menorRegistro, *proxRegistroEntrada;
  Funcionario *reservatorio[elementosPorParticao];

  int contador = 0;
  int posicaoArquivoEntrada = 0;
  int posicaoMenorArray = 0;
  int posicaoArquivoSaida = 0;
  int posReservatorio = 0;

  if (arq != NULL)
  {
    while (contador < elementosPorParticao)
    {
      fseek(arq, posicaoArquivoEntrada * sizeof(Funcionario), SEEK_SET);
      array[contador] = RecuperarFuncionario(arq);
      contador++;
      posicaoArquivoEntrada++;
    }

    char *nome_particao = nomesArquivos->nome;
    nomesArquivos = nomesArquivos->prox;

    FILE *arquivoSaida;
    arquivoSaida = fopen(nome_particao, "wb+");

    do
    {
      posicaoMenorArray = MenorChave(array, elementosPorParticao);
      menorRegistro = array[posicaoMenorArray];

      if (arquivoSaida != NULL)
      {
        SalvarArquivoDeSaida(arquivoSaida, posicaoArquivoSaida, menorRegistro);
        posicaoArquivoSaida++;
      }

      fseek(arq, (posicaoArquivoEntrada) * sizeof(Funcionario), SEEK_SET);
      proxRegistroEntrada = RecuperarFuncionario(arq);
      array[posicaoMenorArray] = proxRegistroEntrada;
      posicaoArquivoEntrada++;

      if (feof(arq))
      {
        posicaoMenorArray = MenorChave(array, elementosPorParticao);
        menorRegistro = array[posicaoMenorArray];
        SalvarArquivoDeSaida(arquivoSaida, posicaoArquivoSaida, menorRegistro);
        break;
      }
      if (proxRegistroEntrada->codigo < menorRegistro->codigo)
      {

        if (posicaoArquivoEntrada < qtdFuncionarios)
        {

          reservatorio[posReservatorio] = proxRegistroEntrada;
          posReservatorio++;

          posicaoArquivoEntrada++;
          fseek(arq, (posicaoArquivoEntrada) * sizeof(Funcionario), SEEK_SET);
          proxRegistroEntrada = RecuperarFuncionario(arq);
          array[posicaoMenorArray] = proxRegistroEntrada;
        }
        else
        {
          reservatorio[posReservatorio] = proxRegistroEntrada;
          array[posicaoMenorArray] = NULL;

          posicaoMenorArray = MenorChave(array, elementosPorParticao);
          menorRegistro = array[posicaoMenorArray];
          if (arquivoSaida != NULL)
          {
            SalvarArquivoDeSaida(arquivoSaida, posicaoArquivoSaida, menorRegistro);
            posicaoArquivoSaida++;
          }

          posReservatorio++;
        }
      }

      if (posReservatorio >= elementosPorParticao)
      {
        fclose(arquivoSaida);

        for (int i = 0; i < posReservatorio; i++)
        {
          array[i] = reservatorio[i];
        }

        for (int r = 0; r < elementosPorParticao; r++)
        {
          reservatorio[r] = NULL;
        }
        posReservatorio = 0;

        char *nome_particao = nomesArquivos->nome;
        nomesArquivos = nomesArquivos->prox;

        arquivoSaida = fopen(nome_particao, "wb+");
        posicaoArquivoSaida = 0;
      }
    } while (posReservatorio < elementosPorParticao);
  }
}
