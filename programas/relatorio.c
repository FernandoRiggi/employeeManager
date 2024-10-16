#include "../headers/pessoa.h"
#include "../headers//pesquisa.h"
#include "../headers/resposta.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gravar_telefones(struct Pessoa *vet_pessoa, int cont_pessoa, char cpf[]){
	FILE *arquivo;
	if((arquivo=fopen("../relatorios/telefones.txt", "w"))==NULL){
		printf("\nErro na criação do arquivo");
		exit(0);
	}
	int i=0;
	int j=0;
	fprintf(arquivo, "----\n");
	for(i;i<cont_pessoa;i++){
		if(strcmp(vet_pessoa[i].cpf, cpf)==0	){
			fprintf(arquivo, "CPF: %s", cpf);
			for(j;j<vet_pessoa[i].cont_tel;j++){
				fprintf(arquivo, "\nTelefone %d: %s", j+1, vet_pessoa[i].telefones[j]);
			}
		}	
	}
	fclose(arquivo);
	printf("\nTelefones gravados com sucesso em 'telefones.txt'");
}

void mostrar_desc_resposta(struct RespostaPesquisa r[], const char codigo[], const char data[], int cont_resposta, struct Pesquisa p[], int cont_pesquisa){
	FILE *arquivo;
	if((arquivo=fopen("../relatorios/descricaoPesquisaEmData.txt", "w"))==NULL){
		printf("\nErro na criação do arquivo");
		exit(0);
	}
	int i, j=0;
	
	for(i=0;i<cont_pesquisa;i++){
		if(strcmp(p[i].codigo, codigo)==0){
			fprintf(arquivo, "---Descrição da pesquisa %s: %s---\n", codigo, p[i].descricao);
			break;
		}
	}

	for(i=0;i<cont_resposta;i++){
		if(strcmp(r[i].data, data)==0 && strcmp(r[i].codigoPesquisa, codigo)==0){
			fprintf(arquivo, "Resposta n°%d, da pesquisa %s\n", j+1, r[i].resposta);
			j++;
			}
		}
	if(j==0){
		fprintf(arquivo, "Não há uma pesquisa registrada com esse código\n");
	}
	fclose(arquivo);
}

struct tm criarStructTm(const char *dataStr){
	struct tm data = {0};
	sscanf(dataStr, "%d/%d/%d", &data.tm_mday, &data.tm_mon, &data.tm_year);
	data.tm_mon -=1;
	data.tm_year -=1900;
	return data;
}

void mostrarPesquisasEntreDatas(time_t inicio, time_t fim, struct RespostaPesquisa *r, int contPesquisa, int contResposta, struct Pesquisa *p, char inicioStr[], char fimStr[]){
	FILE *arquivo;
	if((arquivo=fopen("../relatorios/pesquisaEntreDatas.txt", "w"))==NULL){
		printf("\nErro na criação do arquivo");
		exit(0);
	}
	
	int i=0, j;
	fprintf(arquivo, "---Pesquisas realizadas entre %s e %s---\n", inicioStr, fimStr);
	
	for(i;i<contResposta;i++){
		struct tm dataPesquisa = criarStructTm(r[i].data);
		time_t tempoPesquisa = mktime(&dataPesquisa);
	
		if(tempoPesquisa>=inicio&& tempoPesquisa<=fim){
			for(j=0;j<contPesquisa;j++){
				if(strcmp(r[i].codigoPesquisa, p[j].codigo)==0){
					char dataLimpa[20];
					sscanf(r[i].data, "%[^\n]", dataLimpa);
					
					fprintf(arquivo, "Código: %s, Descrição: %s, Data: %s\n",p[j].codigo, p[j].descricao, dataLimpa);
				}
			}
		}
	}
	fclose(arquivo);
}