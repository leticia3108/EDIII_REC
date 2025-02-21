#include "../include/ex1.h"
#include "../include/ex2.h"
#include "../include/ex3.h"
#include "../include/ex4.h"
#include "../include/ex5.h"
#include "../include/ex6.h"

int LeCabecalho (FILE* arqBin, sCab* cab){
/* Lê o conteúdo do cabeçalho e o armazena na struct sCab. Retorna 0 em caso
   de inconscistência e 1 caso contrário.   
   O arquivo deve ser posicionado no local correto antes de chamar a função e
   após utilizá-la.*/

    fseek (arqBin, 0, SEEK_SET);
    fread(&(cab->status), sizeof(char), 1, arqBin);
    fread(&(cab->topo), sizeof(int), 1, arqBin);
    fread(&(cab->proxRRN), sizeof(int), 1, arqBin);
    fread(&(cab->nroRegRem), sizeof(int), 1, arqBin);
    fread(&(cab->nroPagDisco), sizeof(int), 1, arqBin);
    fread(&(cab->qttCompacta), sizeof(int), 1, arqBin);

    int ret = 0;

    if (cab->status == '1'){
        ret = 1;
    }

    return ret;
    
}

char (*TrataAspas(char (*varg) [ARG_TAM], int n))[ARG_TAM]{
/* Junta os argumentos obtidos com "LeArgumento" que contenham aspas.*/

    int i = 0;
    int temp = 1;
    int cnt = 0;
    char (*vargFinal) [ARG_TAM] = malloc (n * 2 * 3 * ARG_TAM * sizeof(char));

    for (i = 0; i < n; i++){
        if (varg[i][0] == '"'){
            if (varg[i][strlen(varg[i])-1] != '"'){
            while (varg[i+temp][strlen(varg[i+temp])-1] != '"' && (strlen(varg[i+temp])-1) < n){
               //Juntando varg[i] com varg[i + temp]
                strcat(varg[i], " ");
                strcat(varg[i], varg[i+temp]);
                temp++;
            }
            varg[i+temp][strlen(varg[i+temp])-1] = '\0';
            //Juntando varg[i] com varg[i + temp]
            strcat(varg[i], " ");
            strcat(varg[i], varg[i+temp]);
            //Copiando varg[i] em vargFinal[i-cnt]
            strcpy(vargFinal[i-cnt], varg[i]+1);
            i += temp;
            cnt += temp;}
            else {
                strcpy(vargFinal[i-cnt], varg[i]+1);
                vargFinal[i-cnt][strlen(vargFinal[i-cnt])-1] = '\0';
            }
        } else {
            //Copiando varg[i] em vargFinal[i-cnt]
            strcpy(vargFinal[i-cnt], varg[i]);}
    }

    free(varg);

    return vargFinal;

}

int ChaveCampo(char* strCampo){
/* Converte os argumentos fornecidos pelo usuário ("nome", "especie",
 "habitat", ...) em um número inteiro.*/

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
    } else if (strcmp(strCampo, "velocidade") == 0){
        return CHAVE_VELOCIDADE;
    }

    return -1;
}

int ComparaCampo(sDados* dado, char* comp, int chave){
/* Para cada chave, obtida com "ChaveCampo", compara os dados armazenados na
struct sDados com a string fornecida em "comp", retornando 1 caso sejam 
iguais e 0 caso contrário.*/

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

int LeArgumento(char (*varg) [ARG_TAM]){
/* Lê uma linha inserida na entrada padrão (stdin), separa os argumentos
   pelos delimitadores espaço e '\n' e os insere no vetor previamente a-
   locado "varg".*/

    int i = 0;
    char linha[LIN_TAM];
    fgets(linha, LIN_TAM, stdin);

    char* token = strtok (linha, " \n");
    
    while (token){
        strcpy(varg[i], token);
        token = strtok (NULL, " \n");
        i++;
    }

    return i;
}

int ImprimeSDado(const sDados* dado) {
/* Imprime os dados armazenados na struct sDados no formato especificado.*/
    if (dado->removido == '1'){
        return 0;}
    
    printf("Nome: %s\n", dado->nome);
    printf("Especie: %s\n", dado->especie);
    if (strcmp(dado->tipo,"") != 0){
        printf("Tipo: %s\n", dado->tipo);
    }
    printf("Dieta: %s\n", dado->dieta);
    if (strcmp(dado->habitat,"") != 0){
        printf("Lugar que habitava: %s\n", dado->habitat);
    }
    if (dado->tamanho != -1){
        printf("Tamanho: %.1f m\n", dado->tamanho);
    }
    if (dado->velocidade != -1){
        printf("Velocidade: %d %cm/h\n", dado->velocidade, dado->unidadeMedida);
    }

    printf("\n");

    return 1;

}


int VerificaCabecalho (FILE* arqBin){
/* Verifica o status do arquivo binário, retornando 0 em caso de inconscistên-
   cia e 1 caso contrário.   
   O arquivo deve ser posicionado no local correto antes de chamar a função e
   é reposicionado para o começo dos registros de dados após a chamada. */

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
/* Lê um registro de dados do arquivo binário e o armazena em uma struct.   
   O arquivo deve ser posicionado no local correto antes de chamar a função e
   após utilizá-la.*/

   char linha[REG_DADOS];
   char* regVar = malloc (REG_DADOS * sizeof(char));
   char* regVarOrg = regVar;

   if (!(fread(linha, sizeof(char), REG_DADOS, arqBin))){
        return 0;
   }

   dado->removido = linha[0];

   if (dado->removido == '1'){
    dado->populacao = -1;
    dado->tamanho = -1;
    dado->unidadeMedida = '$';
    dado->velocidade = -1;

    strcpy(dado->nome, "");
    strcpy(dado->especie, " ");
    strcpy(dado->habitat, " ");
    strcpy(dado->tipo, " ");
    strcpy(dado->dieta, " ");
    strcpy(dado->alimento, " ");
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

void EscreveCabecalho(FILE* arqBin, sCab cab){
/* Armazena o conteúdo da struct sCab no cabeçalho do arquivo. 
   O arquivo deve ser posicionado no local correto antes de chamar a função e
   após utilizá-la.*/

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
/* Armazena o conteúdo da struct sDados em um registro do binário.
   O arquivo deve ser posicionado no local correto antes de chamar a função e
   após utilizá-la.*/

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
/* Lê uma linha do arquivo "csv" e armazena os dados, já formatados, na struct
de dados (sDados)*/

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

    free (orgLinha);

    return 1;

}

int main() {
    // Leitura da entrada inicial do usuário.
    int opcao = 0;
    scanf("%d", &opcao);
 
    getc(stdin);

    switch (opcao){
        case 1:
            ex1();
            break;
         case 2:
            ex2();
            break;
        case 3:
            ex3();
            break;
        case 4:
            ex4();
            break;
        case 5:
            ex5();
            break;
        case 6:
            ex6();
            break;
        default:
            printf("\nEntrada inválida\n");
            return 1;
    }

    return 0;
}