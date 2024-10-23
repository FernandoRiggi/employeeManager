#include "../headers/pessoa.h"
#include "../headers/pesquisa.h"
#include "../headers/resposta.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int alocar_memoria(void **vetor, int capacidade, int tamanho){
    *vetor = malloc(capacidade * tamanho);
    if(*vetor == NULL){
        printf("\nErro ao alocar memória");
        return 0;
    }
    else{
        printf("\nAlocado com sucesso");
        return 1;
    }
}

int realocar_memoria(void **vetor, int capacidade, int tamanho){
    *vetor = realloc(*vetor, capacidade * tamanho);
    if(*vetor == NULL){
        printf("\nErro ao realocar memória");
        return 0;
    }
    else{
        printf("\nRealocado com sucesso");
        return 1;
    }
}