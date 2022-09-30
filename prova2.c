#include <stdlib.h>
#include <stdio.h>
#include "prova2.h"
#include "func.h"

void selecaoSubstituicao(FILE* arq, int m, int max){
    FILE* particao = fopen("particao.dat", "wb+");
    Funcionario memory[m];
    Funcionario menorFunc;
    int menorCodigo = max+1;
    int position=0;
    for(int i=0;i<m;i++){
        fseek(arq, i * sizeof(Funcionario), SEEK_SET);
        memory[i] = *RecuperarFuncionario(arq);
        if(memory[i].codigo<menorCodigo){
            menorCodigo=memory[i].codigo;
            menorFunc=memory[i];
            position=i;
        }
    }
    for(int i=0;i<m;i++){
        ImprimirFuncionario(&memory[i]);
    }
    SalvarEmArquivo(&menorFunc,particao);
    printf("\n MENOR FUNCIONARIO: \n");
    fseek(particao, 0, SEEK_SET);
    ImprimirFuncionario(RecuperarFuncionario(particao));




    /*for(int i=0;i<m;i++){
        ImprimirFuncionario(&memory[i]);
    }*/
}