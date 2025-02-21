#include "../include/ex3.h"

void ex3(){
    int n = 0;
    char nomeArq[ARG_TAM];
    scanf("%s %d", nomeArq, &n);
    getc(stdin);

    char(*varg)[ARG_TAM];
    varg = malloc (n * 2 * 3 * ARG_TAM * sizeof(char));
    LeArgumento(varg);

    varg = TrataAspas(varg, n * 2 * 3);

    int i;

    FILE* arqBin = fopen(nomeArq, "rb");

    if ( VerificaCabecalho(arqBin) == 0){
        return;
    };

    int chave;
    int regImp, numReg ,numPag;

    sDados* dado = malloc (sizeof(sDados));

    for (i = 0; i < n; i++){
        if (i != 0){
            printf ("\n");
        }
        numReg = 0;
        regImp = 0;
        fseek(arqBin, PAG_TAM, SEEK_SET);
        printf("Busca %d\n", i+1);

        chave = ChaveCampo(varg[2*i]);

        while (LeBinario(arqBin, dado)){
            numReg++;
            if (ComparaCampo(dado, varg[2*i+1], chave)){
                regImp += ImprimeSDado(dado);
            }
        }
        
        if (regImp == 0){
            printf("Registro inexistente.\n\n");
        }

        numPag = (numReg/10) + ((numReg % 10) > 0) + 1;

        printf ("Numero de paginas de disco: %d\n", numPag);
    }

    fclose(arqBin);
    free(varg);
    free(dado);
}