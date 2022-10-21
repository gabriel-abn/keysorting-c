#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "menu.h"
#include "func.h"
#include "prova2.h"
#include "selecao-natural.h"
#define M 199

void MENU_OPCOES()
{
  printf("\n------- Gabriel Antonio - 19.1.8029 ------\n");
  printf("\n------- Luis Guilherme - 19.1.8025 -------\n");
  printf("\n------------------ MENU ------------------\n");
  printf("\n1. PROCURAR FUNCIONARIO - SEQUENCIAL\n");
  printf("\n2. PROCURAR FUNCIONARIO - BUSCA BINARIA\n");
  printf("\n3. ORDENAR VIA KEYSORTING\n");
  printf("\n4. CRIAR NOVA BASE DE DADOS\n");
  printf("\n5. SELECAO NATURAL\n");
  printf("\n6. SELECAO POR SUBSTITUICAO\n");
  printf("\n7. CARREGAR BANCO DE FUNCIONARIOS PARA TABELA HASH\n");
  printf("\n8. BUSCAR FUNCIONARIO NA TABELA HASH\n");
  printf("\n9. IMPRIMIR CONTEUDO DA TABELA HASH\n");
  printf("\n0. SAIR ******************************\n\n");
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
  system("cls");
}

Funcionario tabelaHash[M];
FILE *Hash;

void inicializarTabela(FILE *arq){
    for(int i = 0; i < M; i++){
      // fseek(arq, i * sizeof(Funcionario), SEEK_SET);
      
    }
}
int gerarCodigoHash(int chave){
    return chave % M;
}
void carregarTabela(FILE *arq, FILE *table, int tam_arq){
  for (int i = 0; i < tam_arq; i++)
  {
    fseek(arq, i * sizeof(Funcionario), SEEK_SET);
    Funcionario *funcionario = RecuperarFuncionario(arq);
    int cod = funcionario->codigo;
    int indice = gerarCodigoHash(cod);
    while(tabelaHash[indice].codigo != -1)
        indice = gerarCodigoHash(indice + 1);
    // tabelaHash[indice] = *funcionario;
    
    fseek(table, indice * sizeof(Funcionario), SEEK_SET);
    SalvarEmArquivo(funcionario, table);
    
  }
}
Funcionario* buscaHash(FILE *arq, int chave){
    int indice = gerarCodigoHash(chave);
    Funcionario *funcionario;
    do{
      fseek(arq, indice * sizeof(Funcionario), SEEK_SET);
      funcionario = RecuperarFuncionario(arq);
        if(funcionario->codigo == chave)
            ImprimirFuncionario(funcionario);
        else
            indice = gerarCodigoHash(indice + 1);
    }while(funcionario->codigo != NULL && funcionario->codigo != chave);
    return NULL;
}
void imprimir(FILE *arq){
    printf("\n------------------------TABELA---------------------------\n");
    for(int i = 0; i < M; i++){
      fseek(arq, i * sizeof(Funcionario), SEEK_SET);
      Funcionario *funcionario = RecuperarFuncionario(arq);
        if(funcionario->codigo != -1){
            printf("%2d =", i);
            ImprimirFuncionario(funcionario);
            printf("\n");
        }else{
            printf("%2d =\n", i);
        }
    }
    printf("\n----------------------------------------------------------\n");
}
int chave;



Lista *iniciarLista()
{
  Lista *list = CriarLista("p1.dat", CriarLista("p2.dat", CriarLista("p3.dat", CriarLista("p4.dat", CriarLista("p5.dat", CriarLista("p6.dat", CriarLista("p7.dat", CriarLista("p8.dat", CriarLista("p9.dat", CriarLista("p10.dat", NULL))))))))));
  return list;
}

Lista *iniciarListaSubstituicao()
{
  Lista *list = CriarLista("p1s.dat", CriarLista("p2s.dat", CriarLista("p3s.dat", CriarLista("p4s.dat", CriarLista("p5s.dat", CriarLista("p6s.dat", CriarLista("p7s.dat", CriarLista("p8s.dat", CriarLista("p9s.dat", CriarLista("p10s.dat", NULL))))))))));
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
      case 0:
        printf("Saindo...\n");
        exit(0);
        break;
    case 1:
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
      arquivo = fopen("dados.dat", "wb+");
      CriarBaseDeDados(arquivo, quantidadeFuncionario, codigos);
      printf("Base de dados criada!\n");
      CLEAR_CONSOLE();
      ordenado = false;
      break;
    case 5:
      arquivo = fopen("dados.dat", "rb");
      Lista *list = iniciarLista();
      if (arquivo == NULL)
      {
        printf("Erro!\n");
        break;
      }
      ImprimeNomes(list);
      SelecaoNatural(arquivo, list, 6, 100, 6);

      Funcionario aux;
      FILE *teste;
      for (int i = 0; i < 10; i++)
      {
        teste = fopen("p1.dat", "rb");
        fseek(teste, i * sizeof(Funcionario), SEEK_SET);
        ImprimirFuncionario(RecuperarFuncionario(teste));
      }

      break;
    case 6:
      arquivo = fopen("dados.dat", "rb");
      Lista *lista = iniciarListaSubstituicao();
      if (arquivo == NULL)
      {
        printf("Erro!\n");
        break;
      }
      printf("chamada selecao\n");
      ImprimeNomes(lista);
      selecaoSubstituicao(arquivo, 6, quantidadeFuncionario, lista);
      
      FILE *particao = fopen("p1s.dat", "rb");
      for (int i = 0; i < quantidadeFuncionario; i++)
      {
        if(!feof(particao)){
          fseek(particao, i * sizeof(Funcionario), SEEK_SET);
          Funcionario show = *RecuperarFuncionario(particao);
          ImprimirFuncionario(&show);
        }
      }
      CLEAR_CONSOLE();
      break;
      // HASHING //
      case 7:
        arquivo = fopen("dados.dat", "rb");
        Hash = fopen("HASH.dat", "rb+");
        carregarTabela(arquivo,Hash,quantidadeFuncionario);
        fclose(Hash);
        CLEAR_CONSOLE();
        break;
      case 8:
        printf("Digite o codigo a ser buscado: ");
        Hash = fopen("HASH.dat", "rb");
        scanf("%d", &chave);
        Funcionario retorno = buscaHash(Hash,chave);
        fclose(Hash);
        break;
      case 9:
        Hash = fopen("HASH.dat", "rb");
        imprimir(Hash);
        fclose(Hash);
        CLEAR_CONSOLE();
        break;

    default:
      printf("Opcao invalida!\n");
      CLEAR_CONSOLE();
      break;
    }
  } while (op != 5);
}