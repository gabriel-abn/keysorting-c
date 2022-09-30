#include <stdlib.h>
#include <stdio.h>
#include "prova2.h"
#include "func.h"

void selecaoSubstituicao(FILE* arq, int m, int max){
    //http://www2.ic.uff.br/~vanessa/material/ed2/04-ClassificacaoExterna.pdf
    FILE* particao = fopen("particao.dat", "wb+");          
    Funcionario memory[m];
    //Funcionario* congelados;
    Funcionario congelados[max];
    Funcionario aux;
    for(int i=0;i<max;i++) congelados[i].codigo=-1;
    Funcionario menorFunc;
    int prox = m;
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
    SalvarEmArquivo(&menorFunc,particao);
    fseek(arq, prox * sizeof(Funcionario), SEEK_SET);
    prox++;
    aux=*RecuperarFuncionario(arq);
    if(aux.codigo<menorCodigo){
        for(int i=0;i<max;i++){
            if(congelados[i].codigo==-1){
                congelados[i]=aux; break;
            }
        }
    }else{
        memory[position]=aux;
    }
    
    /*for(int i=0;i<m;i++){
        ImprimirFuncionario(&memory[i]);
    }
    printf("\n MENOR FUNCIONARIO: \n");
    fseek(particao, 0, SEEK_SET);
    ImprimirFuncionario(RecuperarFuncionario(particao));
    */
}