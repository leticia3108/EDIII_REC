#include "../include/ex2.h"

int LeCabecalho (FILE* arqBin){

    char status;
    fread(&status, 1, 1, arqBin);
    fseek(arqBin, 1600, SEEK_SET);

    if (status == '0'){
        printf("Falha no processamento do arquivo.");
        return 0;
    } else {
        return 1;
    }
}

int LeBinario(FILE* arqBin, sDados* dado){

   char linha[REG_DADOS];
   char* regVar = malloc (REG_DADOS * sizeof(char));
   char* regVarOrg = regVar;

   if (!(fread(linha, sizeof(char), REG_DADOS, arqBin))){
        return 0;
   }

   dado->removido = linha[0];

   if (dado->removido == '1'){
    return 1;}

   memcpy(&(dado->encadeamento), linha + 1, 4);

   memcpy(&(dado->populacao), linha + 5, 4);

   memcpy(&(dado->tamanho), linha + 9, 4);

   strncpy(&(dado->unidadeMedida), linha + 13, 1);

   memcpy(&(dado->velocidade), linha + 14, 4);

   strncpy(regVar, linha + 18, REG_DADOS - 18);

   strcpy(dado->nome, strsep (&regVar, "#"));

   strcpy(dado->especie, strsep (&regVar, "#"));

   strcpy(dado->habitat, strsep (&regVar, "#"));

   strcpy(dado->tipo, strsep (&regVar, "#"));

   strcpy(dado->dieta, strsep (&regVar, "#"));

   strcpy(dado->alimento, strsep (&regVar, "#"));

   free (regVarOrg);

   return 1;
}


void ex2(){

    char(*varg)[ARG_TAM];
    varg = malloc (ARG_TAM * sizeof(char));
    LeArgumento(varg);

    FILE* arqBin = fopen(varg[0], "rb");
    if (!arqBin){
        printf("Erro ao abrir o arquivo binario (%s).\n", varg[0]);
        return ;
    }

    sDados* dado = malloc(sizeof(sDados));

    int numReg = 0;

    if ( LeCabecalho(arqBin) == 0){
        return;
    };

    if (!LeBinario(arqBin, dado)){
        printf("Registro inexistente.");
        return;
    } else {
        numReg += imprimeSDado(dado);
        while (LeBinario(arqBin,dado)){
            numReg += imprimeSDado(dado);
        }
    }

    int numPag = (numReg/10) + ((numReg % 10) > 0) + 1;

    printf("Numero de paginas de disco: %d\n", numPag);


    free(dado);
    free(varg);

}