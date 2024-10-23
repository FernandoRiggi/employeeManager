#include "../headers/pessoa.h"
#include "../headers/memoria.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int consultar_cpf(struct Pessoa p[], int cont, const char cpf[])
{
	for(int i=0; i<cont; i++){
		if(strcmp(p[i].cpf, cpf)==0){
		return i;
		}
	}
	return -1;
}

int inserir_pessoas(struct Pessoa **p, int *cont, int *capacidade)
{
	if(*cont>=*capacidade){
		*capacidade *=2; //dobra o tamanho de capacidade
		if(!realocar_memoria((void**)p, *capacidade, sizeof(struct Pessoa))){
			return 0;
		}
	}
	
	char cpf[15];
	printf("\nEntre com o seu CPF: ");
	fgets(cpf, sizeof(cpf), stdin);
	cpf[strcspn(cpf, "\n")] = '\0';

	int k =consultar_cpf(*p, *cont, cpf);
	int i=0;
	if(k==-1){
			
		printf("\nEntre com o seu nome: ");
		fgets((*p)[*cont].nome, sizeof((*p)[*cont].nome), stdin);
		(*p)[*cont].nome[strcspn((*p)[*cont].nome, "\n")] = '\0';
		strcpy((*p)[*cont].cpf, cpf);
		printf("\nEntre com a sua data de nascimento: ");
		fgets((*p)[*cont].data_nasc, sizeof((*p)[*cont].data_nasc), stdin);
		(*p)[*cont].data_nasc[strcspn((*p)[*cont].data_nasc, "\n")] = '\0';
		printf("\nEntre com o seu sexo, 'M' para masculino, 'F' para feminino, 'O' para outros: ");
		(*p)[*cont].sexo = getchar();
		getchar();
		printf("\nEntre com o seu grau de escolaridade: ");
		fgets((*p)[*cont].grau_escolaridade, sizeof((*p)[*cont].grau_escolaridade), stdin);
		(*p)[*cont].grau_escolaridade[strcspn((*p)[*cont].grau_escolaridade, "\n")] = '\0';
		
		do{
		printf("\nEntre com a quantidade de telefones que deseja adicionar, máximo de 10 telefones por pessoa: ");
		scanf("%d", &((*p)[*cont].cont_tel));
		getchar();

		if((*p)[*cont].cont_tel<1 || (*p)[*cont].cont_tel>10){
			printf("\nQuantidade inválida! Entre com um número entre 1 e 10");
			}
		}while((*p)[*cont].cont_tel < 1 || (*p)[*cont].cont_tel > 10);
		int i=0;
		for(i;i<(*p)[*cont].cont_tel;i++){
			printf("\nEntre com o telefone n°%d: ", i+1);
			fgets((*p)[*cont].telefones[i], sizeof((*p)[*cont].telefones), stdin);
			(*p)[*cont].telefones[i][strcspn((*p)[*cont].telefones[i], "\n")] = '\0';		
		}
		(*cont)++;
		return 1;
		}
	return 0;
}

int consultar_pessoas(struct Pessoa p[], int cont, char cpf[])
{
	int k = consultar_cpf(p, cont, cpf);
	if(k!=-1){
		printf("\nNome: %s", p[k].nome);
		printf("\nCPF: %s", p[k].cpf);
		printf("\nData de nascimento: %s", p[k].data_nasc);
		printf("\nSexo: %c", p[k].sexo);
		printf("\nGrau de escolaridade: %s", p[k].grau_escolaridade);
		int i=0;
		for(i;i<p[k].cont_tel;i++){
			printf("\nTelefone n° %d: %s", i+1, p[k].telefones[i]);
		}
		return 1;
		}
	if(k==-1){
	printf("\nPessoa com CPF %s não encontrado", cpf);
	return 0;}
}

void imprimir_pessoas(struct Pessoa p[], int cont)
{
	if(cont==0){
		printf("\nNão há pessoas registradas");
	}
	for(int i=0; i<cont; i++){
		printf("\n\nNome: %s", p[i].nome);
		printf("\nCPF: %s", p[i].cpf);
		printf("\nData de nascimento: %s", p[i].data_nasc);
		printf("\nSexo: %c", p[i].sexo);
		printf("\nGrau de escolaridade: %s", p[i].grau_escolaridade);
		int j=0;
		for(j;j<p[i].cont_tel;j++){
			printf("\nTelefone n° %d: %s",j+1, p[i].telefones[j]);
		}
	}
}

int remover_pessoas(struct Pessoa p[], int *cont, char cpf[])
{
	int k = consultar_cpf(p, *cont, cpf);
	if(k==-1){
		printf("\nPessoa com CPF %s não encontrado", cpf);
		return 0;
	}
	for(k; k<*cont; k++){
		strcpy(p[k].nome, p[k+1].nome);
		strcpy(p[k].cpf, p[k+1].cpf);
		strcpy(p[k].data_nasc, p[k+1].data_nasc);
		p[k].sexo = p[k+1].sexo;
		strcpy(p[k].grau_escolaridade, p[k+1].grau_escolaridade);
		p[k].cont_tel =  p[k+1].cont_tel;
		int i=0;
		for(i;i<p[k].cont_tel;i++){
			strcpy(p[k].telefones[i], p[k+1].telefones[i]);
		}
	}
	(*cont)--;
	return 1;
}

int alterar_pessoa(struct Pessoa p[], int cont, const char cpf[])
{
	int k = consultar_cpf(p, cont, cpf);
	if(k!=-1){
		printf("\nEntre com o nome da pessoa: ");
		fgets(p[k].nome, sizeof(p[k].nome), stdin);
		p[k].nome[strcspn(p[k].nome, "\n")] = '\0';
		printf("\nEntre com a data de nascimento da pessoa: ");
		fgets(p[k].data_nasc, sizeof(p[k].data_nasc), stdin);
		p[k].data_nasc[strcspn(p[k].data_nasc, "\n")] = '\0';
		printf("\nEntre com o seu sexo, 'M' para masculino, 'F' para feminino, 'O' para outros: ");
		p[k].sexo = getchar();
		printf("\nEntre com o grau de escolaridade: ");
		fgets(p[k].grau_escolaridade, sizeof(p[k].grau_escolaridade), stdin);
		p[k].grau_escolaridade[strcspn(p[k].grau_escolaridade, "\n")] = '\0';
		do{
		printf("\nEntre com a quantidade de telefones que deseja adicionar, máximo de 10 telefones por pessoa: ");
		scanf("%d", &(p)[k].cont_tel);
		getchar();

		if(p[k].cont_tel<1 || p[k].cont_tel>10){
			printf("\nQuantidade inválida! Entre com um número entre 1 e 10");
			}
		}while(p[k].cont_tel < 1 || p[k].cont_tel > 10);
		int i=0;
		for(i;i<p[k].cont_tel;i++){
			printf("\nEntre com o telefone n°%d: ", i+1);
			fgets(p[k].telefones[i], sizeof(p[k].telefones), stdin);
			p[k].telefones[i][strcspn(p[k].telefones[i], "\n")] = '\0';		
		}
		return 1;
	}else{
		return 0;
	}
}

void gravarPessoas(struct Pessoa *vet_pessoa, int cont_pessoa){
	FILE *arquivo;
	if((arquivo = fopen("../relatorios/pessoa.dat", "wb"))==NULL){
		printf("Erro na criação do arquivo");
		exit(0);
	}
	int i=0;
	for(i;i<cont_pessoa;i++){
		fwrite(&vet_pessoa[i], sizeof(struct Pessoa),1, arquivo);
	}
	fclose(arquivo);
}

void ler_pessoa(struct Pessoa **vet_pessoa, int *cont_pessoa, int *capacidade_pessoa){
	FILE *arquivo;
	long tamanho;
	int n_pessoa;
	
	arquivo = fopen("../relatorios/pessoa.dat", "rb");
	if(arquivo==NULL){
		printf("\nNâo foi possível abrir o arquivo para leitura.");
		return;
	}
	int resultado;

	fseek(arquivo, 0, SEEK_END);
	tamanho=ftell(arquivo);
	rewind(arquivo);

	n_pessoa = tamanho/sizeof(struct Pessoa);

	if(n_pessoa>*capacidade_pessoa){
		struct Pessoa *temp = realloc(*vet_pessoa, n_pessoa * sizeof(struct Pessoa));
		if(temp == NULL){
			printf("\nErro ao alocar memória para ler os dados");
			fclose(arquivo);
			return;
	}
		*vet_pessoa=temp;
		*capacidade_pessoa=n_pessoa;

	}
		
	resultado = fread(*vet_pessoa, sizeof(struct Pessoa), n_pessoa, arquivo);
	if(resultado!=n_pessoa){
			printf("\nErro ao ler os dados do arquivo");
		}else{
			printf("Lidos com sucesso");
			*cont_pessoa = n_pessoa;
		}
	fclose(arquivo);
	
}