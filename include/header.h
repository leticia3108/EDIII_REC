#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARG_TAM 30
#define STR_TAM 50
#define LIN_TAM 500
#define REG_CAB 160

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

#endif