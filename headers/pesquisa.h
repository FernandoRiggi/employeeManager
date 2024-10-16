#ifndef PESQUISA_H
#define PESQUISA_H

struct Pesquisa{
	char codigo[10];
	char descricao[100];
};

int consultar_codigo(struct Pesquisa p[], int cont, const char codigo[]);

int inserir_pesquisa( struct Pesquisa **p, int *cont, int *capacidade);

int consultar_pesquisa(struct Pesquisa p[], int cont, char codigo[]);

void imprimir_pesquisas(struct Pesquisa p[], int cont);

int remover_pesquisa(struct Pesquisa p[], int *cont, char codigo[]);

int alterar_pesquisa(struct Pesquisa p[], int cont, const char codigo[]);

void ler_pesquisa(struct Pesquisa **vet_pesquisa, int *cont_pesquisa, int *capacidade_pesquisa);

void gravar_pesquisa(struct Pesquisa *vet_pesquisa, int cont_pesquisa);


#endif