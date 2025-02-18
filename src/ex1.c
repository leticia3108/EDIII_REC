#include "../include/ex1.h"
#include "../include/funcoes_fornecidas.h"

void EscreveCabecalho(FILE* arqDados, FILE* arqBin, sCab cab){
    fwrite (&cab.status, sizeof(char), 1, arqBin);
    fwrite (&cab.topo, sizeof(int), 1, arqBin);
    fwrite (&cab.proxRRN, sizeof(int), 1, arqBin);
    fwrite (&cab.nroRegRem, sizeof(int), 1, arqBin);
    fwrite (&cab.nroPagDisco, sizeof(int), 1, arqBin);
    fwrite (&cab.qttCompacta, sizeof(int), 1, arqBin);
    int i = 0;
    char c = '$';
    for (i = 0; i < 1579; i++){
        fwrite(&c, sizeof(char), 1, arqBin);
    }
}

int EscreveBinario(FILE* arqBin, const sDados dado){
    char del = '#';
    fwrite(&dado.removido, sizeof(char), 1, arqBin);
    fwrite(&dado.encadeamento, sizeof(int), 1, arqBin);
    fwrite(&dado.populacao, sizeof(int), 1, arqBin);
    fwrite(&dado.tamanho, sizeof(float), 1, arqBin);
    fwrite(&dado.unidadeMedida, sizeof(char), 1, arqBin);
    fwrite(&dado.velocidade, sizeof(int), 1, arqBin);

    fwrite(dado.nome, sizeof(char), strlen(dado.nome), arqBin);
    fwrite (&del, sizeof(char), 1, arqBin);
    fwrite(dado.especie, sizeof(char), strlen(dado.especie), arqBin);
    fwrite (&del, sizeof(char), 1, arqBin);
    fwrite(dado.habitat, sizeof(char), strlen(dado.habitat), arqBin);
    fwrite (&del, sizeof(char), 1, arqBin);
    fwrite(dado.tipo, sizeof(char), strlen(dado.tipo), arqBin);
    fwrite (&del, sizeof(char), 1, arqBin);
    fwrite(dado.dieta, sizeof(char), strlen(dado.dieta), arqBin);
    fwrite (&del, sizeof(char), 1, arqBin);
    fwrite(dado.alimento, sizeof(char), strlen(dado.alimento), arqBin);
    fwrite (&del, sizeof(char), 1, arqBin);

    int reg = REG_CAB - (strlen(dado.nome) + strlen(dado.especie) + strlen(dado.habitat)
    + strlen(dado.tipo) + strlen(dado.dieta) + strlen(dado.alimento) + 
    6 + 3*sizeof(int) + 2 * sizeof(char) + sizeof(float));

    char fill = '$';
    while (reg > 0){
        fwrite (&fill, sizeof(char), 1, arqBin);
        reg--;
    }

    return 1;

}

int LeLinhaCSV(FILE* arqDados, sDados* dado){

    char* linha = malloc (sizeof(char) * LIN_TAM);
    char* orgLinha = linha;

    if(!fgets(linha, LIN_TAM, arqDados))
        return 0;

    char* token;

    dado->removido = '0';
    dado->encadeamento = -1;

    strcpy(dado->nome, strsep(&linha, ",\n"));

    strcpy(dado->dieta, strsep (&linha, ",\n"));

    strcpy(dado->habitat, strsep (&linha, ",\n"));

    token = strsep (&linha, ",\n");

    dado->populacao = (*token) ? atoi(token) : -1;

    strcpy(dado->tipo, strsep (&linha, ",\n"));

    token = strsep (&linha, ",\n");
    dado->velocidade = (*token) ? atoi(token) : -1;

    token = strsep (&linha, ",\n");
    dado->unidadeMedida = (*token) ? token[0] : '$';

    token = strsep (&linha, ",\n");
    dado->tamanho = (*token)? atof(token) : -1;
    
    strcpy(dado->especie, strsep (&linha, ",\n"));

    strcpy(dado->alimento, strsep (&linha, ",\n\r\0"));

    //printSDados(dado);
    free (orgLinha);

    return 1;

}

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

    EscreveCabecalho(arqDados, arqBin, cab);

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
    EscreveCabecalho(arqDados, arqBin, cab);


    fclose (arqBin);
    binarioNaTela(varg[1]);
    
    fclose(arqDados);
    free(varg);
}