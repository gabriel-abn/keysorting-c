#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "menu.h"

// Gabriel Antonio Batista Nascimento - 19.1.8029
// Luis Guilherme Lopes Aguiar - 19.1.8025
// CSI104

int main()
{
int op, chave;
    // inicializarTabela();
  FILE *arquivo;
  clock_t tempoBinarioComeco, tempoBinarioFim;
  double tempoExecucaoBinario = 0.0;
  int quantidadeFuncionario = 100;
  int arrayChaves[quantidadeFuncionario];
  Funcionario *func;

  FILE *bancoDeDados;

  int codigos[100] = {7, 43, 69, 38, 23, 29, 16, 19, 47, 84, 56, 31, 18, 5, 2, 52, 36, 1, 64, 45, 75, 100, 98, 15, 57, 73, 35, 24, 65, 17, 82, 99, 30, 71, 80, 9, 92, 28, 68, 50, 42, 48, 90, 32, 86, 83, 46, 93, 74, 34, 58, 33, 10, 87, 76, 79, 51, 62, 11, 95, 77, 97, 44, 55, 37, 72, 41, 54, 13, 53, 26, 25, 12, 67, 91, 14, 60, 96, 40, 61, 39, 3, 88, 20, 59, 85, 27, 63, 4, 22, 8, 21, 66, 81, 89, 70, 6, 94, 49, 78};

  MENU(arquivo, quantidadeFuncionario, codigos, bancoDeDados);

  free(func);
  fclose(arquivo);
  fclose(bancoDeDados);

  return 0;
}
