#ifndef PROVA2_H
#define PROVA2_H

#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include <stdbool.h>
#include "selecao-natural.h"

void selecaoSubstituicao(FILE *arq, int m, int max, Lista *nomesArquivos);
bool isCongelado(int func, int con[], int m);
int menorChaveComCongelados(Funcionario *array[], int size, int con[]);


#endif