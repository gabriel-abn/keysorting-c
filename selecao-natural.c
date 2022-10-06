#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "selecao-natural.h"
#include "func.h"

char *cria_str(char *str)
{
  char *s = (char *)calloc(strlen(str) + 1, sizeof(char));
  strcpy(s, str);
  return s;
}

Lista *cria(char *nome, Lista *prox)
{
  printf("cria\n");
  Lista *nomes = (Lista *)malloc(sizeof(Lista));
  nomes->nome = nome;
  nomes->prox = prox;
  return nomes;
}

void libera(Lista *nomes)
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

int conta(Lista *nomes)
{
  int qtd = 0;
  while (nomes)
  {
    qtd += 1;
    nomes = nomes->prox;
  }
  return qtd;
}

void inverte(Lista *nomes)
{
  int i;
  int qtd = conta(nomes);
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

void imprime(Lista *nomes)
{
  while (nomes)
  {
    printf("| %s ", nomes->nome);
    nomes = nomes->prox;
  }
  printf("\n\n");
}

int menorChave(Funcionario *array[], int size)
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

void salva_ArqSaida(FILE *saida, int indice, Funcionario *item)
{
  fseek(saida, (indice) * sizeof(Funcionario), SEEK_SET);
  SalvarEmArquivo(item, saida);
}

void ImprimeNomes(Lista *nomes)
{
  printf("Imprimir nomes\n");
  Lista *aux = nomes->prox;
  for (int i = 0; aux != NULL; i++)
  {
    puts(aux->nome);
    aux = aux->prox;
  }
}

void selecao_natural(FILE *arq, Lista *nome_arquivos_saida, int M, int nFunc, int n)
{
  rewind(arq);

  Funcionario *array[M], *menorRegistro, *proxRegistroEntrada;
  Funcionario *reservatorio[M];

  int count = 0;
  int posArqEntrada = 0;
  int posMenorArray = 0;
  int posArqSaida = 0;
  int posReservatorio = 0;

  /* LER M REGISTROS DO ARQUIVO PARA A MEMÓRIA */
  if (arq != NULL)
  {
    while (count < M)
    {
      fseek(arq, posArqEntrada * sizeof(Funcionario), SEEK_SET);
      array[count] = RecuperarFuncionario(arq);
      count++;
      posArqEntrada++;
      printf("fseek\n");
    }

    printf("_____________________________________________________________________________\n");
    /* GRAVAR O REGISTRO DE MENOR CHAVE NA PARTIÇÃO DE SAÍDA */
    char *nome_particao = nome_arquivos_saida->nome;
    nome_arquivos_saida = nome_arquivos_saida->prox;

    // printf("======Abrindo novo arquivo de saida=====\n");
    FILE *arquivoSaida;
    arquivoSaida = fopen(nome_particao, "wb+");

    /* CASO AINDA EXISTA ESPAÇO LIVRE NO RESERVATÓRIO */
    printf("selecao_natural\n");
    do
    {
      /* SELECIONAR NO ARRAY EM MEMÓRIA, O REGISTRO R COM MENOR CHAVE */
      posMenorArray = menorChave(array, M);
      menorRegistro = array[posMenorArray];

      if (arquivoSaida != NULL)
      {
        // printf("======Salva menor registro no Arq Saida: %d -- %s \n", menorRegistro->codigo, menorRegistro->nome);
        salva_ArqSaida(arquivoSaida, posArqSaida, menorRegistro);
        posArqSaida++;
      }

      /* SUBSTITUIR NO ARRAY EM MEMÓRIA O MENOR REGISTRO PELO PRÓXIMO DO ARQUIVO DE ENTRADA */
      fseek(arq, (posArqEntrada) * sizeof(Funcionario), SEEK_SET);
      proxRegistroEntrada = RecuperarFuncionario(arq);
      array[posMenorArray] = proxRegistroEntrada;
      posArqEntrada++;

      /*
       * CASO A CHAVE DO PROXIMO REGISTRO DE ENTRADA SEJA MENOR DO QUE O MENOR REGISTRO
       * GRAVA NO RESERVATÓRIO E SUBSTITUI NO ARRAY DE MEMÓRIA O MENOR REGISTRO PELO PROXIMO REGISTRO DE ENTRADA
       */
      if (feof(arq))
      {
        posMenorArray = menorChave(array, M);
        menorRegistro = array[posMenorArray];
        salva_ArqSaida(arquivoSaida, posArqSaida, menorRegistro);
        break;
      }
      if (proxRegistroEntrada->codigo < menorRegistro->codigo)
      {
        /* GRAVA NO RESERVATÓRIO */
        if (posArqEntrada < nFunc)
        {

          reservatorio[posReservatorio] = proxRegistroEntrada;
          posReservatorio++;

          /* SUBSTITUIR NO ARRAY EM MEMÓRIA O MENOR REGISTRO PELO PROXIMO REGISTRO DO ARQUIVO DE ENTRADA */
          posArqEntrada++;
          fseek(arq, (posArqEntrada) * sizeof(Funcionario), SEEK_SET);
          proxRegistroEntrada = RecuperarFuncionario(arq);
          array[posMenorArray] = proxRegistroEntrada;

          // array[posMenorArray] = proxRegistroEntrada;
        }
        else
        {
          reservatorio[posReservatorio] = proxRegistroEntrada;
          array[posMenorArray] = NULL;

          posMenorArray = menorChave(array, M);
          menorRegistro = array[posMenorArray];
          if (arquivoSaida != NULL)
          {
            salva_ArqSaida(arquivoSaida, posArqSaida, menorRegistro);
            posArqSaida++;
          }

          posReservatorio++;
        }
      }

      if (posReservatorio >= M)
      {
        /* FECHAR A PARTIÇÃO DE SAÍDA */
        fclose(arquivoSaida);

        /* COPIAR OS REGISTROS DO RESERVATÓRIO PARA O ARRAY EM MEMÓRIA */
        for (int i = 0; i < posReservatorio; i++)
        {
          array[i] = reservatorio[i];
        }

        /* ESVAZIAR O RESERVATÓRIO */
        for (int r = 0; r < M; r++)
        {
          reservatorio[r] = NULL;
        }
        posReservatorio = 0;

        /* ABRIR NOVO ARQUIVO DE SAÍDA */
        char *nome_particao = nome_arquivos_saida->nome;
        nome_arquivos_saida = nome_arquivos_saida->prox;

        arquivoSaida = fopen(nome_particao, "wb+");
        posArqSaida = 0;
      }
    } while (posReservatorio < M);
  }
}
