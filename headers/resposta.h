#ifndef RESPOSTA_H
#define RESPOSTA_H

struct RespostaPesquisa{
	char cpf[15];
	char codigoPesquisa[10];
	char data[20];
	char resposta[500];
};

int consultar_cpf_codigo_resposta(struct RespostaPesquisa rp[], int cont, const char cpf[], const char codigo[]);

int inserir_resposta(struct Pessoa **f, struct Pesquisa **p, struct RespostaPesquisa **rp, int *cont_pessoa, int *cont_pesquisa, int *cont_resposta, int *capacidade);

int consultar_resposta(struct RespostaPesquisa rp[], int cont, char codigo[], char cpf[]);

void imprimir_respostas(struct RespostaPesquisa rp[], int cont);

int remover_respostas(struct RespostaPesquisa rp[], int *cont, char codigo[], char cpf[]);

int alterar_resposta(struct RespostaPesquisa rp[], int cont, const char codigo[], const char cpf[]);

void ler_resposta(struct RespostaPesquisa **vet_resposta, int *cont_resposta, int *capacidade_resposta);

void gravar_resposta(struct RespostaPesquisa *vet_resposta, int cont_resposta);

#endif