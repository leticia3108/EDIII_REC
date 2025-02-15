#include "../include/ex1.h"

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
             //ex2();
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