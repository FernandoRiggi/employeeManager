#include "../headers/pessoa.h"
#include "../headers/pesquisa.h"
#include "../headers/resposta.h"
#include "../headers/relatorio.h"
#include "../headers/menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Portuguese");
	int capacidade_pessoa = 50;
	int cont_pessoa = 0;
	struct Pessoa *vet_pessoa = malloc(capacidade_pessoa * sizeof(struct Pessoa));	
	if(vet_pessoa== NULL){
		printf("\nErro ao alocar memória");
		return 1;}
	int capacidade_pesquisa = 50;
	int cont_pesquisa =0;
	struct Pesquisa *vet_pesquisa = malloc(capacidade_pesquisa * sizeof(struct Pesquisa));
	if(vet_pesquisa==NULL){
		printf("\nErro ao alocar memória");
		return 1;
	}
	int capacidade_resposta = 50;
	int cont_resposta =0;
	struct RespostaPesquisa *vet_resposta = malloc(capacidade_resposta * sizeof(struct RespostaPesquisa));
	if(vet_resposta==NULL){
		printf("\nErro ao alocar memória");
		return 1;
	}
	int op_menu, op_pessoa, op_pesquisa, op_resposta_pesquisa, op_relatorios;
	char cpf[15];
	char codigo_pesquisa[10];
	char pessoa[7] = "PESSOA"; char pessoas[8] = "PESSOAS"; char pesquisa[9] = "PESQUISA"; char pesquisas[10]="PESQUISAS";
	char resposta[9] = "RESPOSTA"; char respostas[10]="RESPOSTAS";
	char codigo_resposta[10];
	do{
		op_menu = menu();
		switch(op_menu){
			case 1:{
				ler_pessoa(&vet_pessoa, &cont_pessoa, &capacidade_pessoa);
				do{	
					op_pessoa=menus(pessoas, pessoa);
					switch (op_pessoa){
						case 1:{
							printf("\nInciando opção inserir");
							if(inserir_pessoas(&vet_pessoa, &cont_pessoa, &capacidade_pessoa))
								{printf("\nInserido com sucesso");}
							else{printf("\nNão foi possível inserir");}
							break;
						}
						case 2:{
							printf("\nInciando opção consultar");
							printf("\nEntre com o CPF da pessoa que deseja buscar: ");
							fgets(cpf, sizeof(cpf), stdin);
							cpf[strcspn(cpf, "\n")] = '\0';
							consultar_pessoas(vet_pessoa, cont_pessoa, cpf);
							break;
						}
						case 3:{
							printf("\nInciando opção imprimir");
							imprimir_pessoas(vet_pessoa, cont_pessoa);
							break;
						}
						case 4:{
							printf("\nInciando opção remover");
							printf("\nEntre com o CPF da pessoa que deseja remover: ");
							fgets(cpf, sizeof(cpf), stdin);
							cpf[strcspn(cpf, "\n")] = '\0';
							if(remover_pessoas(vet_pessoa, &cont_pessoa, cpf)==1){printf("\nRemovido com sucesso!");
							}else{printf("\nNão foi possível remover!");
							}
							break;
						}
						case 5:{
							printf("\nIniciando opção alterar");
							printf("\nEntre com o CPF da pessoa que deseja alterar: ");
							fgets(cpf, sizeof(cpf), stdin);
							cpf[strcspn(cpf, "\n")] = '\0'; 
							if(alterar_pessoa(vet_pessoa, cont_pessoa, cpf)==1){
								printf("\nAlterado com sucesso!");
							}else{
								printf("\nNão foi possível alterar!");
							}
							break;
						}
						case 6:{
							printf("\nRetornando ao Menu Principal");
							gravarPessoas(vet_pessoa, cont_pessoa);
							break;
						}
						default:{
							printf("\nOperação inválida");
							break;
						}
					}
				} while(op_pessoa!=6);
				break;
			}
			case 2:{
				ler_pesquisa(&vet_pesquisa, &cont_pesquisa, &capacidade_pesquisa);
				do{
					op_pesquisa = menus(pesquisas, pesquisa);
					switch (op_pesquisa)
					{
					case 1:{
						printf("\nInciando opção inserir");
						if(inserir_pesquisa(&vet_pesquisa, &cont_pesquisa, &capacidade_pesquisa)){
							printf("\nInserido com sucesso");
						} else{printf("\nNão foi possível inserir");}
						break;
					}
					case 2:{
						printf("\nIniciando opção consultar");
						printf("\nEntre com o código da pesquisa que deseja buscar: ");
						fgets(codigo_pesquisa, sizeof(codigo_pesquisa), stdin);
						codigo_pesquisa[strcspn(codigo_pesquisa, "\n")] = '\0';
						consultar_pesquisa(vet_pesquisa, cont_pesquisa, codigo_pesquisa);
						break;
					}
					case 3:{
						printf("\nIniciando opção imprimir");
						imprimir_pesquisas(vet_pesquisa, cont_pesquisa);
						break;
					}
					case 4:{
						printf("\nInciando opção remover");
						printf("\nEntre com o código da pesquisa que deseja remover: ");
						fgets(codigo_pesquisa, sizeof(codigo_pesquisa), stdin);
						codigo_pesquisa[strcspn(codigo_pesquisa, "\n")] = '\0';
						if(remover_pesquisa(vet_pesquisa, &cont_pesquisa, codigo_pesquisa)==1){
							printf("\nRemovido com sucesso!");
						}else{printf("\nNão foi possível remover!");}
						break;
					}
					case 5:{
						printf("\nIniciando opção alterar");
						printf("\nEntre com o código da pesquisa que deseja alterar: ");
						fgets(codigo_pesquisa, sizeof(codigo_pesquisa), stdin);
						codigo_pesquisa[strcspn(codigo_pesquisa, "\n")] = '\0';
						if(alterar_pesquisa(vet_pesquisa, cont_pesquisa, codigo_pesquisa)==1){
							printf("\nAlterado com sucesso!");
						}else{printf("\nNão foi possível alterar!");}
						break;
					}
					case 6:{
						printf("\nRetornando ao Menu Principal");
						gravar_pesquisa(vet_pesquisa, cont_pesquisa);
						break;
					}
					default:{
						printf("\nOperação inválida");
						break;
					}
					}
				} while(op_pesquisa!=6);
				break;
			}
			case 3:{
				ler_resposta(&vet_resposta, &cont_resposta, &capacidade_resposta);
				do{
					op_resposta_pesquisa = menus(respostas, resposta);
					switch(op_resposta_pesquisa)
					{
						case 1:{
						printf("\nInciando opção inserir");
						if(inserir_resposta(&vet_pessoa, &vet_pesquisa, &vet_resposta, &cont_pessoa, &cont_pesquisa, &cont_resposta, &capacidade_resposta)){
							printf("\nInserido com sucesso!");
						} else{printf("\nNão foi possível inserir!");}
						break;
					}
					case 2:{
						printf("\nIniciando opção consultar");
						printf("\nEntre com o cpf da pessoa que deseja buscar: ");
						fgets(cpf, sizeof(cpf), stdin);
						cpf[strcspn(cpf, "\n")] = '\0';
						printf("\nEntre com o código da pesquisa que deseja buscar: ");
						fgets(codigo_pesquisa, sizeof(codigo_pesquisa), stdin);
						codigo_pesquisa[strcspn(codigo_pesquisa, "\n")] = '\0';
						consultar_resposta(vet_resposta, cont_resposta, cpf, codigo_pesquisa);
						break;
					}
					case 3:{
						printf("\nIniciando opção imprimir");
						imprimir_respostas(vet_resposta, cont_resposta);
						break;
					}
					case 4:{
						printf("\nInciando opção remover");
						printf("\nEntre com o cpf da pessoa que realizou a resposta que deseja remover");
						fgets(cpf, sizeof(cpf), stdin);
						cpf[strcspn(cpf, "\n")] = '\0';
						printf("\nEntre com código da pesquisa que deseja remover a resposta");
						fgets(codigo_resposta, sizeof(codigo_resposta), stdin);
						codigo_resposta[strcspn(codigo_resposta, "\n")] = '\0';
						if(remover_respostas(vet_resposta, &cont_resposta, codigo_resposta, cpf)==1){
							printf("\nRemovido com sucesso");
						}else{printf("\nNão foi possível remover");}
						break;
					}
					case 5:{
						printf("\nIniciando opção alterar");
						printf("\nEntre com o cpf da pessoa que realizou a resposta que deseja alterar");
						fgets(cpf, sizeof(cpf), stdin);
						cpf[strcspn(cpf, "\n")] = '\0';
						printf("\nEntre com código da pesquisa que deseja alterar a resposta");
						fgets(codigo_resposta, sizeof(codigo_resposta), stdin);
						if(alterar_resposta(vet_resposta, cont_resposta, codigo_resposta, cpf)==1){
							printf("\nAlterado com sucesso");
						}else{printf("\nNão foi possível alterar");}
						break;
					}
					case 6:{
						printf("\nRetornando ao Menu Principal");
						gravar_resposta(vet_resposta, cont_resposta);
						break;
					}
					default:{
						printf("\nOperação inválida");
						break;
					}
					}
				} while(op_resposta_pesquisa!=6);
				break;
			}
			case 4:{
				ler_pessoa(&vet_pessoa, &cont_pessoa, &capacidade_pessoa);
				ler_pesquisa(&vet_pesquisa, &cont_pesquisa, &capacidade_pesquisa);
				ler_resposta(&vet_resposta, &cont_resposta, &capacidade_resposta);				
				do{
					op_relatorios = menu_rel();
					switch(op_relatorios){
						case 1:{
							printf("\nINICIANDO OPÇÃO DE MOSTRAR OS TELEFONES DE UMA PESSOA");
							printf("\nDigite o cpf da pessoa que quer consultar os telefones: ");
							fgets(cpf, sizeof(cpf), stdin);
							cpf[strcspn(cpf, "\n")] = '\0';
							gravar_telefones(vet_pessoa, cont_pessoa, cpf);
							break;
						}
						case 2:{
							printf("\nIniando a opção de mostrar a descrição e respostas de determinada pesquisada realizada em uma data");
							printf("\nEntre com o código da pesquisa que deseja consultar as respostas: ");
							fgets(codigo_pesquisa, sizeof(codigo_pesquisa), stdin);
							codigo_pesquisa[strcspn(codigo_pesquisa, "\n")] = '\0';
							char data[11];
							printf("\nEntre com a data que deseja consultar as respostas da pesquisa: ");
							fgets(data, sizeof(data), stdin);
							data[strcspn(data, "\n")] = '\0';
							mostrar_desc_resposta(vet_resposta, codigo_pesquisa, data, cont_resposta, vet_pesquisa, cont_pesquisa);
							break;
						}
						case 3:{
							printf("\nInciando opção de mostrar o código e a descrição de todas as pesquisas realizadas entres certas datas");
							char dataInicioStr[15], datafimStr[15];
							printf("\nEntre com a data de iníco (dd/mm/aaaa): ");
							fgets(dataInicioStr, sizeof(dataInicioStr), stdin);
							dataInicioStr[strcspn(dataInicioStr, "\n")] = '\0';
							printf("\nEntre com a data de fim (dd/mm/aaaa): ");
							fgets(datafimStr, sizeof(datafimStr), stdin);
							datafimStr[strcspn(datafimStr, "\n")] = '\0';
							struct tm dataInicio = criarStructTm(dataInicioStr);
							struct tm datafim = criarStructTm(datafimStr);
							time_t inicio =mktime(&dataInicio);
							time_t fim = mktime(&datafim);
							mostrarPesquisasEntreDatas(inicio, fim , vet_resposta, cont_pesquisa, cont_resposta, vet_pesquisa,dataInicioStr, datafimStr );
							break;	
						}
						default:{
							printf("\nOperação inválida");
							break;
						}
					}
				} while(op_relatorios!=4);
				break;
			}
		}
	} while(op_menu!=5);

	free(vet_pessoa);
	free(vet_pesquisa);
	free(vet_resposta);
	return 0;
}