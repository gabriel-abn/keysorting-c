#include <stdlib.h>
#include <stdio.h>
#include "prova2.h"
#include "func.h"
#include "selecao-natural.h"
#include <stdbool.h>

/*void selecaoSubstituicao(FILE *arq, int m, int max)
{
    // http://www2.ic.uff.br/~vanessa/material/ed2/04-ClassificacaoExterna.pdf
    FILE *particao = fopen("particao.dat", "wb+");
    Funcionario memory[m];
    // Funcionario* congelados;
    Funcionario congelados[max];
    Funcionario aux;
    for (int i = 0; i < max; i++)
        congelados[i].codigo = -1;
    Funcionario menorFunc;
    int prox = m;
    int menorCodigo = max + 1;
    int position = 0;
/*    for(int iteration=0;iteration<max;iteration++)
    {
        printf("iteration: %d\n", iteration);
        for (int i = 0; i < m; i++)
        {
            if (prox < max)
            {
                fread(&aux, sizeof(Funcionario), 1, arq);
                memory[i] = aux;
                prox++;
            }
            else
            {
        printf("prox>=max\n");
                memory[i].codigo = max + 1;
            }
        }
        for (int i = 0; i < m; i++)
        {
            if (memory[i].codigo < menorCodigo)
            {
                menorCodigo = memory[i].codigo;
                menorFunc = memory[i];
                position = i;
                printf("Funcionario %s de codigo %d e menor que  %s de codigo %d\n", memory[i].nome, memory[i].codigo, menorFunc.nome, menorFunc.codigo);
            }
        }
        memory[position].codigo = max + 1;
        menorCodigo = max + 1;
        fwrite(&menorFunc, sizeof(Funcionario), 1, particao);
    }
    rewind(particao);
    rewind(arq);
    int i = 0;
    for (int iteration = 0; iteration < max; iteration++)
    {
        if (i == m)
            i = 0;
        fread(&aux, sizeof(Funcionario), 1, particao);
        if (congelados[i].codigo == -1)
        {
            congelados[i] = aux;
            i++;
        }
        else
        {
            if (aux.codigo < congelados[i].codigo)
            {
                fwrite(&aux, sizeof(Funcionario), 1, arq);
            }
            else
            {
                fwrite(&congelados[i], sizeof(Funcionario), 1, arq);
                congelados[i] = aux;
                i++;
            }
        }
    }
    for (int j = 0; j < m; j++)
    {
        if (congelados[j].codigo != -1)
            fwrite(&congelados[j], sizeof(Funcionario), 1, arq);
    }
    fclose(particao);
*/
/**/
/*for(int iteration=0;iteration<max;iteration++){
    for (int i = 0; i < m; i++)
    {
        fseek(arq, i * sizeof(Funcionario), SEEK_SET);
        memory[i] = *RecuperarFuncionario(arq);
        if (memory[i].codigo < menorCodigo)
        {
            printf("||||||Funcionario %s de codigo %d e menor que  %s de codigo %d\n", memory[i].nome, memory[i].codigo, menorFunc.nome, menorFunc.codigo);
            menorCodigo = memory[i].codigo;
            menorFunc = memory[i];
            position = i;
        }else{
            printf("Funcionario %s de codigo %d NAO e menor que  %s de codigo %d\n", memory[i].nome, memory[i].codigo, menorFunc.nome, menorFunc.codigo);
        }
    }
    SalvarEmArquivo(&menorFunc, particao);
    fseek(arq, prox * sizeof(Funcionario), SEEK_SET);
    prox++;
    aux = *RecuperarFuncionario(arq);
    if (aux.codigo < menorCodigo)
    {
        printf("CONGELADO | Funcionario %s de codigo %d e menor que  %s de codigo %d\n", aux.nome, aux.codigo, menorFunc.nome, menorFunc.codigo);
        for (int i = 0; i < max; i++)
        {
            if (congelados[i].codigo == -1)
            {
                congelados[i] = aux;
                break;
            }
        }
    }
    else
    {
        memory[position] = aux;
    }
}


    /*for(int i=0;i<m;i++){
        ImprimirFuncionario(&memory[i]);
    }
    printf("\n MENOR FUNCIONARIO: \n");
    fseek(particao, 0, SEEK_SET);
    ImprimirFuncionario(RecuperarFuncionario(particao));
    
}*/
bool isCongelado(int func, int con[], int m)
{
    for (int i = 0; i < m; i++)
    {
        if (con[i] == func)
            return false;
    }
    return true;
}
int menorChaveComCongelados(Funcionario *array[], int size, int con[])
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
      else if (!isCongelado(i,con,size))
      {
        if (menor->codigo > array[i]->codigo)
        {
            menor = array[i];
            posMenor = i;
        }
      }
    }
  }
  else
  {
    return posNotNULL;
  }

  return posMenor;
}

void selecaoSubstituicao(FILE *arq, int m, int max, Lista *nomesArquivos)
{
  rewind(arq);

  Funcionario *array[max], *menorRegistro, *proxRegistroEntrada;
  int congelados[m];

  int count = 0;
  int posArqEntrada = 0;
  int posMenorArray = 0;
  int posArqSaida = 0;
  int posReservatorio = 0;

  /* LER M REGISTROS DO ARQUIVO PARA A MEMÓRIA */
  if (arq != NULL)
  {
    while (count < m)
    {
      fseek(arq, posArqEntrada * sizeof(Funcionario), SEEK_SET);
      array[count] = RecuperarFuncionario(arq);
      count++;
      posArqEntrada++;
      printf("fseek\n");
    }

    printf("_____________________________________________________________________________\n");
    /* GRAVAR O REGISTRO DE MENOR CHAVE NA PARTIÇÃO DE SAÍDA */
    char *nome_particao = nomesArquivos->nome;
    nomesArquivos = nomesArquivos->prox;

    // printf("======Abrindo novo arquivo de saida=====\n");
    FILE *arquivoSaida;
    arquivoSaida = fopen(nome_particao, "wb+");

    /* CASO AINDA EXISTA ESPAÇO LIVRE NO RESERVATÓRIO */
    printf("selecao_substituicao\n");
    do
    {
      /* SELECIONAR NO ARRAY EM MEMÓRIA, O REGISTRO R COM MENOR CHAVE */
      posMenorArray = menorChaveComCongelados(array, m, congelados);
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
        posMenorArray = menorChaveComCongelados(array, m, congelados);
        menorRegistro = array[posMenorArray];
        salva_ArqSaida(arquivoSaida, posArqSaida, menorRegistro);
        break;
      }
      if (proxRegistroEntrada->codigo < menorRegistro->codigo)
      {
        /* GRAVA NO RESERVATÓRIO */
        if (posArqEntrada < max)
        {

          congelados[posReservatorio] = proxRegistroEntrada->codigo;
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
        //   congelados[posReservatorio] = proxRegistroEntrada;
          array[posMenorArray] = NULL;

          posMenorArray = menorChaveComCongelados(array, m, congelados);
          menorRegistro = array[posMenorArray];
          if (arquivoSaida != NULL)
          {
            salva_ArqSaida(arquivoSaida, posArqSaida, menorRegistro);
            posArqSaida++;
          }

          posReservatorio++;
        }
      }

      if (posReservatorio >= m)
      {
        /* FECHAR A PARTIÇÃO DE SAÍDA */
        fclose(arquivoSaida);

        /* ESVAZIAR O RESERVATÓRIO */
        for (int r = 0; r < m; r++)
        {
          congelados[r] = -1;
        }
        posReservatorio = 0;

        /* ABRIR NOVO ARQUIVO DE SAÍDA */
        char *nome_particao = nomesArquivos->nome;
        nomesArquivos = nomesArquivos->prox;

        arquivoSaida = fopen(nome_particao, "wb+");
        posArqSaida = 0;
      }
    } while (posReservatorio < m);
  }
}
