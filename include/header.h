#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARG_TAM 30
#define STR_TAM 50
#define LIN_TAM 500
#define REG_CAB 160
#define REG_DADOS 160
#define PAG_TAM 1600

#define CHAVE_NOME 1
#define CHAVE_ESPECIE 2
#define CHAVE_HABITAT 3
#define CHAVE_TIPO 4
#define CHAVE_DIETA 5
#define CHAVE_ALIMENTO 6
#define CHAVE_POPULACAO 7
#define CHAVE_TAMANHO 8
#define CHAVE_UNIDADE 9
#define CHAVE_VELOCIDADE 10

typedef struct {
    char status;
    int topo;
    int proxRRN;
    int nroRegRem;
    int nroPagDisco;
    int qttCompacta;
} sCab;

typedef struct {
    char removido;
    int encadeamento;
    int populacao;
    float tamanho;
    char unidadeMedida;
    int velocidade;
    char nome[STR_TAM];
    char especie[STR_TAM];
    char habitat[STR_TAM];
    char tipo[STR_TAM];
    char dieta[STR_TAM];
    char alimento[STR_TAM];
} sDados;

int LeArgumento(char (*)[ARG_TAM]);
void printSDados(const sDados* data);
int ImprimeSDado(const sDados* dado);
int LeBinario(FILE* arqBin, sDados* dado);
int VerificaCabecalho (FILE* arqBin);
int LeCabecalho (FILE* arqBin, sCab* cab);
char (*TrataAspas(char (*varg) [ARG_TAM], int n))[ARG_TAM];
int ComparaCampo(sDados* dado, char* comp, int chave);
int ChaveCampo(char* strCampo);
int EscreveBinario(FILE* arqBin, const sDados dado);
void EscreveCabecalho(FILE* arqBin, sCab cab);
int LeLinhaCSV(FILE* arqDados, sDados* dado);
int LeCabecalho (FILE* arqBin, sCab* cab);


#endif