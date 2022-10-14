#include <stdlib.h>
#include <stdio.h>
#include "prova2.h"
#include "func.h"

void selecaoSubstituicao(FILE *arq, int m, int max)
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
    for (int iteration = 0; iteration < max; iteration++)
    {
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
            }
            else
            {
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
    */
}