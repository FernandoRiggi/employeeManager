#include "../headers/pesquisa.h"
#include "../headers/memoria.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int consultar_codigo(struct Pesquisa p[], int cont, const char codigo[])
{
	for(int i=0; i<cont; i++){
		if(strcmp(p[i].codigo, codigo)==0){
			return i;
		}
	}
	return -1;
}

int inserir_pesquisa( struct Pesquisa **p, int *cont, int *capacidade){
	if(*cont>=*capacidade){
		*capacidade *=2; //dobra o tamanho de capacidade
		if(!realocar_memoria((void**)p, *capacidade, sizeof(struct Pesquisa))){
			return 0;
		}
	}
	char codigo[10];
	printf("\nEntre com o código da pesquisa: ");
	fgets(codigo, sizeof(codigo), stdin);
	codigo[strcspn(codigo, "\n")] = '\0';

	int k = consultar_codigo(*p, *cont, codigo);
	if(k==-1){
		printf("\nEntre com a descrição da pesquisa: ");
		fgets((*p)[*cont].descricao, sizeof((*p)[*cont].descricao), stdin);
		(*p)[*cont].descricao[strcspn((*p)[*cont].descricao, "\n")]	= '\0';	
		strcpy((*p)[*cont].codigo, codigo);
		(*cont)++;
		return 1;
	}
	return 0;
}

int consultar_pesquisa(struct Pesquisa p[], int cont, char codigo[])
{
	int k = consultar_codigo(p, cont, codigo);
	if(k!=-1)
	{
		printf("\nDescrição: %s", p[k].descricao);
		return 1;
	}
	if(k==-1){
		printf("\nPesquisa com código %s não encontrada", codigo);
		return 0;
	}
}

void imprimir_pesquisas(struct Pesquisa p[], int cont){
	if(cont==0){
		printf("\nNão há pesquisas registradas");
	}
	for(int i=0; i<cont; i++){
		printf("\n\nCódigo: %s", p[i].codigo);
		printf("\nDescrição: %s", p[i].descricao);
	}
}

int remover_pesquisa(struct Pesquisa p[], int *cont, char codigo[])
{
	int k = consultar_codigo(p, *cont, codigo);
	if(k==-1){
		printf("\nPesquisa com código %s não encontrada", codigo);
		return 0;
	}
	for(k; k<*cont; k++){
		strcpy(p[k].codigo, p[k+1].codigo);
		strcpy(p[k].descricao, p[k+1].descricao);
	}
	(*cont)--;
	return 1;
}

int alterar_pesquisa(struct Pesquisa p[], int cont, const char codigo[])
{
	int k = consultar_codigo(p, cont, codigo);
	if(k!=-1){
		printf("\nEntre com a descrição da pesquisa: ");
		fgets(p[k].descricao, sizeof(p[k].descricao), stdin);
		p[k].descricao[strcspn(p[k].descricao, "\n")] = '\0';
		return 1;
	} else{
		return 0;
	}
}

void ler_pesquisa(struct Pesquisa **vet_pesquisa, int *cont_pesquisa, int *capacidade_pesquisa){
	FILE *arquivo;
	long tamanho;
	int n_pesquisa;
	arquivo = fopen("../relatorios/pesquisa.dat", "rb");
	if(arquivo==NULL){
		printf("\nNão foi possível abrir o arquivo");
		return;
	}

	int resultado;
	fseek(arquivo, 0, SEEK_END);
	tamanho=ftell(arquivo);
	rewind(arquivo);

	n_pesquisa = tamanho/sizeof(struct Pesquisa);

	if(n_pesquisa>*capacidade_pesquisa){
		struct Pesquisa *temp = realloc(*vet_pesquisa, n_pesquisa *sizeof(struct Pesquisa));
		if(temp==NULL){
			printf("\nErro ao ler os dados do arquivo");
			fclose(arquivo);
			return;
		}
		*vet_pesquisa=temp;
		*capacidade_pesquisa = n_pesquisa;
	}

	resultado=fread(*vet_pesquisa, sizeof(struct Pesquisa), n_pesquisa, arquivo);
	if(resultado!=n_pesquisa){
		printf("\nErro ao ler os dados do arquivo");
	}else{
		printf("\nLidos com sucesso");
		*cont_pesquisa=n_pesquisa;
	}
	fclose(arquivo);
}

void gravar_pesquisa(struct Pesquisa *vet_pesquisa, int cont_pesquisa){
	FILE *arquivo;
	if((arquivo=fopen("../relatorios/pesquisa.dat", "wb"))==NULL){
		printf("\nErro na criação do arquivo");
		exit(0);
	}
	int i=0;
	for(i;i<cont_pesquisa;i++){
		fwrite(&vet_pesquisa[i], sizeof(struct Pesquisa), 1, arquivo);
	}
	fclose(arquivo);
}