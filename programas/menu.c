#include "../headers/pessoa.h"
#include "../headers/pesquisa.h"
#include "../headers/resposta.h"
#include "../headers/relatorio.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int menu()
{
	printf("\nMENU PRINCIPAL\n\n");
	printf("\t1. SUBMENU DE PESSOAS\n");
	printf("\t2. SUBMENU DE PESQUISA\n");
	printf("\t3. SUBMENU DE RESPOSTA DE PESQUISA\n");
	printf("\t4. SUBMENU DE RELÁTORIOS\n");
	printf("\t5. ENCERRAR PROGRAMA\n");
	printf("\nESCOLHA UMA OPÇÃO: ");
	int opc;
	scanf("%d", &opc);
	getchar();
	return opc;
}

int menus(char titulo[], char conteudo[])
{
	printf("\nMENU DE OPÇÕES DE %s\n\n", titulo);
	printf("\t1. INSERIR UMA NOVA %s\n", conteudo);
	printf("\t2. CONSULTAR DADOS DE UMA %s\n", conteudo);
	printf("\t3. IMPRIMIR TODAS %s\n", titulo);
	printf("\t4. EXCLUIR UMA %s \n", conteudo);
	printf("\t5. ALTERAR UMA %s\n", conteudo);
	printf("\t6. RETORNAR AO MENU PRINCIPAL\n");
	printf("\nESCOLHA UMA OPÇÃO: ");
	int opc;
	scanf("%d", &opc);
	getchar();
	return opc;
}

int menu_rel(){
	printf("\nMENU DE RELÁTORIOS\n\n");
	printf("\t1. TELEFONES DE UMA PESSOA\n");
	printf("\t2. DESCRIÇÃO E RESPOSTAS DE PESQUISA REALIZADA EM UMA DATA\n");
	printf("\t3. CÓDIGO E DESCRIÇÃO DE PESQUISAS ENTRE DATAS\n");
	printf("\t4. RETORNAR AO MENU PRINCIPAL\n");
	printf("\nESCOLHA UMA OPÇÃO: ");
	int opc;
	scanf("%d", &opc);
	getchar();
	return opc;
}