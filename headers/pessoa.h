#ifndef PESSOA_H
#define PESSOA_H
struct Pessoa
{
	char nome[50], cpf[15];
	char data_nasc[15];
	char sexo;
	int cont_tel;
	char telefones[10][15];
	char grau_escolaridade[30];
};

int consultar_cpf(struct Pessoa p[], int cont, const char cpf[]);

int inserir_pessoas(struct Pessoa **p, int *cont, int *capacidade);

int consultar_pessoas(struct Pessoa p[], int cont, char cpf[]);

void imprimir_pessoas(struct Pessoa p[], int cont);

int remover_pessoas(struct Pessoa p[], int *cont, char cpf[]);

int alterar_pessoa(struct Pessoa p[], int cont, const char cpf[]);

void gravarPessoas(struct Pessoa *vet_pessoa, int cont_pessoa);

void ler_pessoa(struct Pessoa **vet_pessoa, int *cont_pessoa, int *capacidade_pessoa);



#endif /* BIBLIOTECA_H */