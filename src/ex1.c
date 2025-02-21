#include "../include/ex1.h"
#include "../include/funcoes_fornecidas.h"

void ex1(){

    char(*varg)[ARG_TAM];
    varg = malloc (2 * ARG_TAM * sizeof(char));
    LeArgumento(varg);

    FILE* arqDados = fopen(varg[0],"r");

    if (!arqDados){
        printf("Falha no processamento do arquivo.");
        return;
    }


    FILE* arqBin = fopen(varg[1], "w");

    if (!arqBin){
        printf("Erro na criacao do arquivo binario, (%s)", varg[1]);
        fclose(arqDados);
        return;
    }

    sCab cab;
    cab.status = 0;
    cab.topo = -1;
    cab.proxRRN = 0;
    cab.nroRegRem = 0;
    cab.nroPagDisco = 0;
    cab.qttCompacta = 0;

    EscreveCabecalho(arqBin, cab);

    sDados dado;

    char linha[LIN_TAM];
    fgets (linha, LIN_TAM, arqDados);

    int i = 0;
    while (LeLinhaCSV(arqDados, &dado)){
        i += EscreveBinario(arqBin, dado);
    }

    cab.status = '1';
    cab.proxRRN = i;
    cab.nroPagDisco = i/10 + (i%10 >= 1) + 1;

    fseek(arqBin, 0, SEEK_SET);
    EscreveCabecalho(arqBin, cab);


    fclose (arqBin);
    binarioNaTela(varg[1]);
    
    fclose(arqDados);
    free(varg);
}