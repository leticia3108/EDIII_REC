#include "../include/ex2.h"

void ex2(){

    char(*varg)[ARG_TAM];
    varg = malloc (ARG_TAM * sizeof(char));
    LeArgumento(varg);

    FILE* arqBin = fopen(varg[0], "rb");
    if (!arqBin){
        printf("Falha no processamento do arquivo.");
        return ;
    }

    sDados* dado = malloc(sizeof(sDados));

    int numReg = 0;
    int numImp = 0;

    if ( VerificaCabecalho(arqBin) == 0){
        return;
    };

    if (!LeBinario(arqBin, dado)){
        printf("Registro inexistente.");
        return;
    } else {
        numReg ++;
        numImp += ImprimeSDado(dado);
        while (LeBinario(arqBin,dado)){
            numReg ++;
            numImp += ImprimeSDado(dado);
        }
    }

    int numPag = (numReg/10) + ((numReg % 10) > 0) + 1;

    if (numImp == 0){
        printf("Registro inexistente.");
        return;
    }

    printf("Numero de paginas de disco: %d\n", numPag);


    free(dado);
    free(varg);

}