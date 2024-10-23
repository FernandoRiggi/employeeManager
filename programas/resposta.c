#include "../headers/pesquisa.h"
#include "../headers/pessoa.h"
#include "../headers/resposta.h"
#include "../headers/memoria.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int consultar_cpf_codigo_resposta(struct RespostaPesquisa rp[], int cont, const char cpf[], const char codigo[]){
	for(int i=0; i<cont; i++){
		if(strcmp(rp[i].cpf, cpf)==0 && strcmp(rp[i].codigoPesquisa, codigo)==0){
			return i;
		}
	}
	return -1;
}

int inserir_resposta(struct Pessoa **f, struct Pesquisa **p, struct RespostaPesquisa **rp, int *cont_pessoa, int *cont_pesquisa, int *cont_resposta, int *capacidade)
{
	if(*cont_resposta>=*capacidade){
		*capacidade *=2; //dobra a capacidade
		if(!realocar_memoria((void**)p, *capacidade, sizeof(struct RespostaPesquisa))){
			return 0;
		}
	}

	char cpf[15];
	printf("\nEntre com o cpf: ");
	fgets(cpf, sizeof(cpf), stdin);
	cpf[strcspn(cpf, "\n")] = '\0';
	int k = consultar_cpf(*f, *cont_pessoa, cpf);
	if(k==-1){
		printf("\nCPF não encontrado!");
		return 0;
	}
	
	char codigo[10];
	printf("\nEntre com o código: ");
	fgets(codigo, sizeof(codigo), stdin);
	codigo[strcspn(codigo, "\n")] = '\0';
	int k2 = consultar_codigo(*p, *cont_pesquisa, codigo);
	if(k2==-1){
		printf("\nCódigo não encontrado!");
		return 0;
	}

	int index = consultar_cpf_codigo_resposta(*rp, *cont_resposta, cpf, codigo);
	if(index==-1){
	printf("\nEntre com a data da resposta da pesquisa: ");
	fflush(stdin);
	fgets((*rp)[*cont_resposta].data, sizeof((*rp)[*cont_resposta].data), stdin);
	(*rp)[*cont_resposta].data[strcspn((*rp)[*cont_resposta].data, "\n")] = '\0';
	fflush(stdin);
	printf("\nEntre com a resposta da pesquisa: "); 
	fgets((*rp)[*cont_resposta].resposta, sizeof((*rp)[*cont_resposta].resposta), stdin);
	(*rp)[*cont_resposta].resposta[strcspn((*rp)[*cont_resposta].resposta, "\n")] = '\0';
	strcpy((*rp)[*cont_resposta].cpf, cpf);
	strcpy((*rp)[*cont_resposta].codigoPesquisa, codigo);
	(*cont_resposta)++;
	return 1;
	}
	return 0;
}

int consultar_resposta(struct RespostaPesquisa rp[], int cont, char codigo[], char cpf[])
{
	int k = consultar_cpf_codigo_resposta(rp, cont ,cpf ,codigo);
	if(k!=-1){
		printf("\nData da resposta: %s", rp[k].data);
		printf("\nResposta: %s", rp[k].resposta);
		return 1;
	}
	if(k==-1){
		printf("\nResposta com cpf %s e código %s não encontrada", cpf, codigo);
		return 0;
	}
}

void imprimir_respostas(struct RespostaPesquisa rp[], int cont){
	if(cont==0){
		printf("\nNão há respostas registradas");
	}
	for(int i=0; i<cont; i++){
		printf("\n\nCPF: %s", rp[i].cpf);
		printf("\nCódigo: %s", rp[i].codigoPesquisa);
		printf("\nData: %s", rp[i].data);
		printf("\nRespota: %s", rp[i].resposta);

	}
}

int remover_respostas(struct RespostaPesquisa rp[], int *cont, char codigo[], char cpf[]){
	int k = consultar_cpf_codigo_resposta(rp, *cont, cpf, codigo);
	if(k==-1){
		printf("\nResposta com o cpf %s e código %s não encontrada", cpf, codigo);
		return 0;
	}
	for(k; k<*cont; k++){
		strcpy(rp[k].cpf, rp[k+1].cpf);
		strcpy(rp[k].codigoPesquisa, rp[k+1].codigoPesquisa);
		strcpy(rp[k].data, rp[k+1].data);
		strcpy(rp[k].resposta, rp[k+1].resposta);
	}
	(*cont)--;
	return 1;
}

int alterar_resposta(struct RespostaPesquisa rp[], int cont, const char codigo[], const char cpf[])
{
	int k = consultar_cpf_codigo_resposta(rp, cont, codigo, cpf);
	if(k!=-1){
		printf("\nEntre com a resposta da pesquisa: ");
		fgets(rp[k].resposta, sizeof(rp[k].resposta), stdin);
		rp[k].resposta[strcspn(rp[k].resposta, "\n")] = '\0';
		return 1;
	} else{
		return 0;
	}
}

void ler_resposta(struct RespostaPesquisa **vet_resposta, int *cont_resposta, int *capacidade_resposta){
	FILE *arquivo;
	long tamanho;
	int n_resposta;
	arquivo=fopen("../relatorios/resposta.dat", "rb");
	if(arquivo==NULL){
		printf("\nNão foi possível abrir o arquivo");
		return;
	}

	int resultado;
	fseek(arquivo, 0, SEEK_END);
	tamanho=ftell(arquivo);
	rewind(arquivo);

	n_resposta=tamanho/sizeof(struct RespostaPesquisa);

	if(n_resposta>*capacidade_resposta){
		struct RespostaPesquisa *temp = realloc(*vet_resposta, n_resposta *sizeof(struct RespostaPesquisa));
		if(temp==NULL){
			printf("\nErro ao ler os dados do arquivo");
			fclose(arquivo);
			return;
		}
		*vet_resposta=temp;
		*capacidade_resposta=n_resposta;
	}
	
	resultado=fread(*vet_resposta, sizeof(struct RespostaPesquisa), n_resposta, arquivo);
	if(resultado!=n_resposta){
		printf("\nErro ao ler os dados do arquivo");
	}else{
		printf("\nLido com sucesso");
		*cont_resposta=n_resposta;
	}
	fclose(arquivo);
}

void gravar_resposta(struct RespostaPesquisa *vet_resposta, int cont_resposta){
	FILE *arquivo;
	if((arquivo=fopen("../relatorios/resposta.dat", "wb"))==NULL){
		printf("\nErro na criação do arquivo");
		exit(0);
	}
	int i=0;
	for(i;i<cont_resposta;i++){
		fwrite(&vet_resposta[i], sizeof(struct RespostaPesquisa), 1, arquivo);
	}
	fclose(arquivo);
}