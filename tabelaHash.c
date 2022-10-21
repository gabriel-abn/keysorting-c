#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include <stdbool.h>
// constante m = primo mais proximo de (numero de funcionarios * 2)
#define M 199 

void imprimirTabela(Funcionario *tabela){
    printf("-----------TABELA-------------\n");
    for(int i = 0; i < M; i++){
        if(tabela[i].codigo != -1){
            printf("Posicao: %d\n", i);
            ImprimirFuncionario(&tabela[i]);
        }else{
            printf("Posicao: %d\n", i);
            printf("Vazio\n");
        }
    }
}
void inserirTabela(){
    
}
void removerTabela(int chave){
    
}
Funcionario * inicializaHash(Funcionario *tabelaHash){
    for(int i=0;i<M;i++){
        tabelaHash[i].codigo =-1;
    }
    return tabelaHash;
}
int gerarHash(int key){
    return key%M;
}
Funcionario * buscarHash(int chave){
    
}