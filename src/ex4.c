#include "../include/ex4.h"

void RemoveRegBin(FILE* arqBin, int RRN){
/* Remove o registro com o RRN especificado e atualiza o cabeçalho do 
arquivo.*/

    sCab* cab = malloc (sizeof(sCab));
    LeCabecalho (arqBin, cab);

    int topo = cab->topo;
    cab->topo = RRN;
    cab->nroRegRem ++;

    fseek (arqBin, 0, SEEK_SET);

    EscreveCabecalho(arqBin, *cab);

    fseek(arqBin, PAG_TAM + RRN * 160, SEEK_SET);
    
    char status = '1';
    char lixo[REG_DADOS - 5];
    memset(lixo, '$', REG_DADOS - 5);

    fwrite(&status, sizeof(char), 1, arqBin);
    fwrite(&(topo), sizeof(int), 1, arqBin);
    fwrite(&lixo, sizeof(char), REG_DADOS - 5, arqBin);

    free(cab);

}

void ex4(){
    int n = 0;
    char nomeArq[ARG_TAM];
    scanf("%s %d", nomeArq, &n);
    getc(stdin);

    char(*varg)[ARG_TAM];
    varg = malloc (n * 2 * 3 * ARG_TAM * sizeof(char));
    LeArgumento(varg);

    varg = TrataAspas(varg, n * 2 * 3);

    int i;

    FILE* arqBin = fopen(nomeArq, "r+");

    if (!arqBin){
        printf("Falha no processamento do arquivo");
    } 

    if (VerificaCabecalho(arqBin) == 0){
        return;
    };

    int chave, RRN;

    sDados* dado = malloc (sizeof(sDados));

    for (i = 0; i < n; i++){

        RRN = 0;
        int x=0;
        fseek(arqBin, PAG_TAM, SEEK_SET);
     
        chave = ChaveCampo(varg[2*i]);

        while (LeBinario(arqBin, dado)){
    
            if (ComparaCampo(dado, varg[2*i+1], chave)){
                RemoveRegBin(arqBin, RRN);
            }

            RRN++;
            x++;
        }
    
    }

    fclose(arqBin);
    free(varg);
    free(dado);

    binarioNaTela(nomeArq);
}