#ifndef MENU_C
#define MENU_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

void inicializarTabela();

void carregarTabela(FILE *arq, FILE *table, int tam_arq);

// função de espalhamento (resto da divisão da chave por M)
int gerarCodigoHash();

// função para ler e retornar uma pessoa
Pessoa lerPessoa();

// inserir uma pessoa na tabela
void inserir();

Pessoa* buscar(int chave);

void imprimir();
void MENU_OPCOES();
void CLEAR_CONSOLE();
int OPCAO();
void MENU(FILE *arquivo, int quantidadeFuncionario, int *codigos, FILE *banco, Pessoa *p);

#endif