#include "../include/ex1.h"
#include "../include/ex2.h"

int LeArgumento(char (*varg) [ARG_TAM]){
    int i = 0;
    char linha[ARG_TAM];
    fgets(linha, ARG_TAM, stdin);

    char* token = strtok (linha, " \n");
    
    while (token){
        strcpy(varg[i], token);
        //printf("Argumento %d: (%s)\n", i, varg[i]);
        token = strtok (NULL, " \n");
        i++;
    }

       // printf ("Temos %d argumentos", i);
    return i;
}

void printSDados(const sDados* data) {
    printf("\nRemovido: %c\n", data->removido);
    printf("Encadeamento: %d\n", data->encadeamento);
    printf("População: %d\n", data->populacao);
    printf("Tamanho: %.2f %c\n", data->tamanho, data->unidadeMedida);
    printf("Velocidade: %d km/h\n", data->velocidade);
    printf("Nome: %s\n", data->nome);
    printf("Espécie: %s\n", data->especie);
    printf("Habitat: %s\n", data->habitat);
    printf("Tipo: %s\n", data->tipo);
    printf("Dieta: %s\n", data->dieta);
    printf("Alimento: %s\n\n", data->alimento);
}

int imprimeSDado(const sDados* dado) {

    if (dado->removido == '1'){
        return 1;}
    
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

int main() {
    // Leitura da entrada inicial do usuário
    int opcao = 0;
    scanf("%d", &opcao);
   // printf("Foi escolhida a opcao %d\n", opcao);
    getc(stdin);

    switch (opcao){
        case 1:
            ex1();
            break;
         case 2:
             ex2();
             break;
        case 3:
            //ex3();
            break;
        case 4:
            //ex4();
            break;
        case 5:
            //ex5();
            break;
        case 6:
            //ex6();
            break;
        default:
            printf("\nEntrada inválida\n");
            return 1;
    }

    return 0;
}