#ifndef RELATORIO_H
#define RELATORIO_H

#include <time.h>

void gravar_telefones(struct Pessoa *vet_pessoa, int cont_pessoa, char cpf[]);

void mostrar_desc_resposta(struct RespostaPesquisa r[], const char codigo[], const char data[], int cont_resposta, struct Pesquisa p[], int cont_pesquisa);

struct tm criarStructTm(const char *dataStr);

void mostrarPesquisasEntreDatas(time_t inicio, time_t fim, struct RespostaPesquisa *r, int contPesquisa, int contResposta, struct Pesquisa *p, char inicioStr[], char fimStr[]);

#endif