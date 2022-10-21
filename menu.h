#ifndef MENU_C
#define MENU_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

void inicializarTabela();
void carregarTabela(FILE *arq, FILE *table, int tam_arq);
int gerarCodigoHash();
void inserir();
Funcionario* buscaHash(FILE *arq, int chave);
void imprimir(FILE *arq);
void MENU_OPCOES();
void CLEAR_CONSOLE();
int OPCAO();
void MENU(FILE *arquivo, int quantidadeFuncionario, int *codigos, FILE *banco);

#endif