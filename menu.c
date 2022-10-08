#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "menu.h"
#include "func.h"
#include "prova2.h"
#include "selecao-natural.h"

void MENU_OPCOES()
{
  printf("\n------- Gabriel Antonio - 19.1.8029 ------\n");
  printf("\n------- Luis Guilherme - 19.1.8025 -------\n");
  printf("\n------------------ MENU ------------------\n");
  printf("\n1. PROCURAR FUNCIONARIO - SEQUENCIAL\n");
  printf("\n2. PROCURAR FUNCIONARIO - BUSCA BINARIA\n");
  printf("\n3. ORDENAR VIA KEYSORTING\n");
  printf("\n4. CRIAR NOVA BASE DE DADOS\n");
  printf("\n5. SAIR\n");
}

int OPCAO()
{
  int op;
  printf("OPCAO: ");
  fscanf(stdin, "%d%*c", &op);

  return op;
}

void CLEAR_CONSOLE()
{
  char c;
  printf("\n--------------------------------\n");
  printf("Pressione ENTER para continuar...");
  printf("\n--------------------------------\n");
  c = getchar();
  system("clear");
}

void iniciarLista(Lista *list)
{
  list = cria("p1.dat", cria("p2.dat", cria("p3.dat", cria("p4.dat", cria("p5.dat", cria("p6.dat", cria("p7.dat", cria("p8.dat", cria("p9.dat", cria("p10.dat", NULL))))))))));
}

void MENU(FILE *arquivo, int quantidadeFuncionario, int *codigos, FILE *banco)
{
  bool ordenado = false;
  int teste;
  int busca;
  int op;
  arquivo = fopen("dados.dat", "rb+");
  Funcionario *func;

  do
  {
    MENU_OPCOES();
    op = OPCAO();
    switch (op)
    {
    case 1:
      // Questão 2
      // PROCURA SEQUENCIAL
      if (arquivo == NULL)
      {
        printf("\nArquivo nao encontrado. Crie uma base de dados nova...\n");
        CLEAR_CONSOLE();
        break;
      }

      printf("Digite o codigo a ser procurado: ");
      fscanf(stdin, "%d%*c", &busca);

      func = BuscaSequencial(busca, arquivo, quantidadeFuncionario);

      if (func == NULL)
      {
        printf("Funcionario nao encontrado!\n");
        CLEAR_CONSOLE();
        break;
      }

      ImprimirFuncionario(func);
      CLEAR_CONSOLE();
      break;
    case 2:
      // Questão 4
      // PROCURA BINÁRIA
      banco = fopen("BANCO_DE_DADOS.dat", "rb");
      if (arquivo == NULL)
      {
        printf("\nArquivo nao encontrado. Crie uma base de dados nova\n");
        CLEAR_CONSOLE();
        break;
      }
      if (ordenado == false)
      {
        printf("\nArquivo nao ordenado. Ordene a base de dados atraves do menu\n");
        CLEAR_CONSOLE();
        break;
      }

      printf("Digite o codigo a ser procurado: ");
      fscanf(stdin, "%d%*c", &busca);

      func = BuscaBinaria(busca, quantidadeFuncionario, banco);

      if (func == NULL)
      {
        printf("Funcionario nao encontrado!\n");
        CLEAR_CONSOLE();
        break;
      }

      ImprimirFuncionario(func);
      CLEAR_CONSOLE();
      break;
    case 3:
      // Questão 3
      // KEYSORTING
      if (arquivo == NULL)
      {
        printf("\nArquivo nao encontrado. Crie uma base de dados nova...\n");
        CLEAR_CONSOLE();
        break;
      }
      banco = fopen("BANCO_DE_DADOS.dat", "wb+");
      KeySorting(arquivo, banco, quantidadeFuncionario);
      CLEAR_CONSOLE();
      ordenado = true;
      break;
    case 4:
      // Questão 1
      // CRIAR BASE DE DADOS NOVA
      arquivo = fopen("dados.dat", "wb+");
      CriarBaseDeDados(arquivo, quantidadeFuncionario, codigos);
      printf("Base de dados criada!\n");
      CLEAR_CONSOLE();
      ordenado = false;
      break;
    case 5:
      // SAIR
      printf("Saindo...\n");
      exit(0);
      break;
    case 6:
      arquivo = fopen("BANCO_DE_DADOS.dat", "rb");
      Lista *list;
      iniciarLista(list);
      printf("chamada selecao\n");
      selecao_natural(arquivo, list, 6, 100, 3);
      break;
    case 7:
      arquivo = fopen("dados.dat", "rb");
      selecaoSubstituicao(arquivo, 6, quantidadeFuncionario);
      break;
    case 8:

      break;

    default:
      printf("Opcao invalida!\n");
      CLEAR_CONSOLE();
      break;
    }
  } while (op != 5);
}