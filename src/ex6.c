#include "../include/ex5.h"

void ex6(){
    char nomeArq[ARG_TAM];
    scanf("%s", nomeArq);
    getc(stdin);
    FILE* arqBin = fopen(nomeArq, "r");
    FILE* arqTemp = fopen("temp.bin", "w+");

    if (!arqBin){
        printf("Falha no processamento do arquivo.");
        return;
    }

    if (!arqTemp){
        printf("Falha no processamento do arquivo.");
        return;
    }


    sCab cab;
    sDados dado;
    LeCabecalho(arqBin, &cab);
    fseek(arqBin, PAG_TAM, SEEK_SET);

    cab.nroRegRem = 0;
    cab.qttCompacta++;
    cab.proxRRN = 0;
    cab.topo = -1;

    while (LeBinario(arqBin, &dado)){
    
        if (dado.removido == '0'){
            EscreveBinario(arqTemp, dado);
            cab.proxRRN ++;
        }
    }

    cab.nroPagDisco = (cab.proxRRN / 10) + ((cab.proxRRN % 10) > 0) + 1;

    fseek(arqTemp, 0, SEEK_SET);
    fclose(arqBin);
    arqBin = fopen(nomeArq, "w");

    EscreveCabecalho(arqBin, cab);

    while (LeBinario(arqTemp, &dado)){
        EscreveBinario(arqBin, dado);
    }
    
    fclose(arqBin);
    fclose(arqTemp);

    binarioNaTela(nomeArq);

}