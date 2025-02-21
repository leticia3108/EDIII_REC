#include "../include/ex5.h"

void TrataNulos (sDados* dado, char (* varg)[ARG_TAM]){
/* Armazena os argumentos de "varg" na struct de dados (sDados), tratando 
os valores nulos.*/

    dado->removido = '0';
    dado->encadeamento = -1;
    strcpy (dado->nome, varg[0]);
    strcpy (dado->dieta, varg[1]);
    if (strcmp(varg[2],"NULO") == 0){
        strcpy(dado->habitat, "");
    } else {
        strcpy(dado->habitat, varg[2]);
    }
    if (strcmp(varg[3],"NULO") == 0){
        dado->populacao = -1;
    } else {
        dado->populacao = atoi(varg[3]);
    }
    if (strcmp(varg[4],"NULO") == 0){
        strcpy(dado->tipo, "");
    } else {
        strcpy(dado->tipo, varg[4]);
    }
    if (strcmp(varg[5],"NULO") == 0){
        dado->velocidade = -1;
    } else {
        dado->velocidade = atoi(varg[5]);
    }
    if (strcmp(varg[6],"NULO") == 0){
        dado->unidadeMedida = '$';
    } else {
        dado->unidadeMedida = varg[6][0];
    }
    if (strcmp(varg[7],"NULO") == 0){
        dado->tamanho = -1;
    } else {
        dado->tamanho = atof(varg[7]);
    }
    if (strcmp(varg[8],"NULO") == 0){
        strcpy(dado->especie, "");
    } else {
        strcpy(dado->especie, varg[8]);
    }
    if (strcmp(varg[9],"NULO") == 0){
        strcpy(dado->alimento, "");
    } else {
        strcpy(dado->alimento, varg[9]);
    }

}

int SobreescreveBinario(FILE* arqBin, sDados dado){
/* Sobreescreve o registro de dados apontado por "topo" no cabeçalho com os
   dados da struct sDados. Se não houver registros removidos, o adiciona os
   novos dados no final do arquivo.*/

    sCab cab;
    LeCabecalho(arqBin, &cab);
    if (cab.topo == -1){
        fseek(arqBin, 0, SEEK_END);
        cab.proxRRN++;
        cab.nroPagDisco = (cab.proxRRN / 10) + ((cab.proxRRN % 10) > 0) + 1;
    } else {
    fseek (arqBin, PAG_TAM + cab.topo * 160 + 1, SEEK_SET);
    cab.nroRegRem --;
    fread (&(cab.topo), sizeof(int), 1 , arqBin);
    fseek (arqBin, -5, SEEK_CUR);}

    EscreveBinario(arqBin, dado);
    fseek (arqBin, 0, SEEK_SET);
    EscreveCabecalho(arqBin, cab);
    fseek (arqBin, 0, SEEK_SET);
    return 1;
}

void ex5(){

    int n = 0;
    char nomeArq[ARG_TAM];
    scanf("%s %d", nomeArq, &n);
    getc(stdin);

    char(*varg)[ARG_TAM];
    varg = malloc (n * 20 * ARG_TAM * sizeof(char));

    int i = 0;

    for (i = 0; i < n; i++){
    LeArgumento(&(varg[i*10]));
    varg = TrataAspas(varg, 20 * n);
    }

    sDados* dado = malloc (sizeof (sDados));
    FILE* arqBin = fopen (nomeArq, "r+");

    if (!arqBin){
        printf ("Falha no processamento do arquivo.");
        return;
    }

    for (i = 0; i < n; i++){
        TrataNulos (dado, &(varg[10*i]));
        SobreescreveBinario(arqBin, *dado);
    }

    free (dado);
    free (varg);
    fclose (arqBin);
    binarioNaTela (nomeArq);
}