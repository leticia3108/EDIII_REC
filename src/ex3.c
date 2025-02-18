#include "../include/ex3.h"

char (*TrataAspas(char (*varg) [ARG_TAM], int n))[ARG_TAM]{

    int i = 0;
    int temp = 1;
    int cnt = 0;
    char (*vargFinal) [ARG_TAM] = malloc (n * 2 * 3 * ARG_TAM * sizeof(char));

    for (i = 0; i < n; i++){
        if (varg[i][0] == '"'){
            if (varg[i][strlen(varg[i])-1] != '"'){
            while (varg[i+temp][strlen(varg[i+temp])-1] != '"' && (strlen(varg[i+temp])-1) < n){
               // printf("Juntando varg[%d] com varg[%d]\n", i, i+temp);
                strcat(varg[i], " ");
                strcat(varg[i], varg[i+temp]);
                temp++;
            }
            varg[i+temp][strlen(varg[i+temp])-1] = '\0';
            //printf("Juntando varg[%d] com varg[%d]\n", i, i+temp);
            strcat(varg[i], " ");
            strcat(varg[i], varg[i+temp]);
            //printf("Copiando varg[%d] em vargFinal[%d]\n", i, i-cnt);
            strcpy(vargFinal[i-cnt], varg[i]+1);
            i += temp;
            cnt += temp;}
            else {
                strcpy(vargFinal[i-cnt], varg[i]+1);
                vargFinal[i-cnt][strlen(vargFinal[i-cnt])-1] = '\0';
            }
        } else {
            //printf("Copiando varg[%d] em vargFinal[%d]\n", i, i-cnt);
            strcpy(vargFinal[i-cnt], varg[i]);}
    }

    free(varg);

    return vargFinal;

}

int ChaveCampo(char* strCampo){
    if (strcmp(strCampo, "nome") == 0){
        return CHAVE_NOME;
    } else if (strcmp(strCampo, "especie") == 0){
        return CHAVE_ESPECIE;
    } else if (strcmp(strCampo, "habitat") == 0){
        return CHAVE_HABITAT;
    } else if (strcmp(strCampo, "tipo") == 0){
        return CHAVE_TIPO;
    } else if (strcmp(strCampo, "dieta") == 0){
        return CHAVE_DIETA;
    } else if (strcmp(strCampo, "alimento") == 0){
        return CHAVE_ALIMENTO;
    } else if (strcmp(strCampo, "populacao") == 0){
        return CHAVE_POPULACAO;
    } else if (strcmp(strCampo, "tamanho") == 0){
        return CHAVE_TAMANHO;
    } else if (strcmp(strCampo, "unidadeMedida") == 0){
        return CHAVE_UNIDADE;
    } else if (strcmp(strCampo, "unidadeMedida") == 0){
        return CHAVE_VELOCIDADE;
    }

    return -1;
}

int ComparaCampo(sDados* dado, char* comp, int chave){

    switch (chave){
        case CHAVE_NOME:
            if (strcmp(comp, dado->nome) == 0){
                return 1;
            }
            break;
        case CHAVE_ESPECIE:
            if (strcmp(comp, dado->especie) == 0){
                return 1;
            }
            break;
        case CHAVE_HABITAT:
            if (strcmp(comp, dado->habitat) == 0){
                return 1;
            }
            break;
        case CHAVE_TIPO:
            if (strcmp(comp, dado->tipo) == 0){
                return 1;
            }
            break;
        case CHAVE_DIETA:
            if (strcmp(comp, dado->dieta) == 0){
                return 1;
            }
            break;
        case CHAVE_ALIMENTO:
            if (strcmp(comp, dado->alimento) == 0){
                return 1;
            }
            break;
        case CHAVE_POPULACAO:
            return (dado->populacao == atoi(comp));
            break;
        case CHAVE_TAMANHO:
            return (dado->tamanho == atof(comp));
            break;
        case CHAVE_VELOCIDADE:
            return (dado->velocidade == atoi(comp));
            break;
        case CHAVE_UNIDADE:
            return (dado->unidadeMedida == comp[0]);
            break;
    }

    return 0;
}

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

    /*
    for (i = 0; i < 6* n; i++){
        printf("varg[%d] = %s\n", i, varg[i]);
    } */

    FILE* arqBin = fopen(nomeArq, "rb");

    if ( LeCabecalho(arqBin) == 0){
        return;
    };

    int chave;
    int regImp = 0;
    sDados* dado = malloc (sizeof(sDados));
    for (i = 0; i < n; i++){
        printf("Busca %d\n", i+1);
        chave = ChaveCampo(varg[3+2*n]);
        while (LeBinario(arqBin, dado)){
            if (ComparaCampo(dado, varg[3+2*n+1], chave)){
                regImp += imprimeSDado(dado);
            }
        }
        
        if (regImp == 0){
            printf("Registro inexistente.\n\n");
        }


    }

    fclose(arqBin);
    free(varg);
    free(dado);
}