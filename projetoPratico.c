#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

struct Funcionario
{
	char nome[50], cpf[15];
	char cargo[30];
	int dependentes;
	float salario;
};

struct Pesquisa{
	char codigo[10];
	char descricao[100];
};

struct RespostaPesquisa{
	char cpf[15];
	char codigoPesquisa[10];
	char data[11];
	char resposta[500];
};

int consultar_cpf(struct Funcionario f[], int cont, const char cpf[])
{
	for(int i=0; i<cont; i++){
		if(strcmp(f[i].cpf, cpf)==0){
		return i;
		}
	}
	return -1;
}

int inserir_funcionario(struct Funcionario **f, int *cont, int *capacidade)
{
	if(*cont>=*capacidade){
		*capacidade+=50;
		*f = realloc(*f, (*capacidade) * sizeof(struct Funcionario));
		if(*f == NULL){
			printf("\nErro ao realocafr memória.");
			return 0;
		}
	}
		char cpf[15];
		printf("\nEntre com o seu CPF: ");
		fgets(cpf, sizeof(cpf), stdin);
		cpf[strcspn(cpf, "\n")] = '\0';

		int k =consultar_cpf(*f, *cont, cpf);
		if(k==-1){
			
			printf("\nEntre com o seu nome: ");
			fgets((*f)[*cont].nome, sizeof((*f)[*cont].nome), stdin);
			(*f)[*cont].nome[strcspn((*f)[*cont].nome, "\n")] = '\0';
			strcpy((*f)[*cont].cpf, cpf);
			printf("\nEntre com o seu cargo: ");
			fgets((*f)[*cont].cargo, sizeof((*f)[*cont].cargo), stdin);
			(*f)[*cont].cargo[strcspn((*f)[*cont].cargo, "\n")] = '\0';
			printf("\nEntre com o número de dependentes: ");
			scanf("%d", &(*f)[*cont].dependentes);
			getchar();
			printf("\nEntre com o salário-base: ");
			scanf("%f", &(*f)[*cont].salario);
			getchar();
			(*cont)++;
			return 1;
		}
	return 0;
}

int consultar_funcionario(struct Funcionario f[], int cont, char cpf[])
{
	int k = consultar_cpf(f, cont, cpf);
	if(k!=-1){
		printf("\nNome: %s", f[k].nome);
		printf("\nCargo: %s", f[k].cargo);
		printf("\nSalário: %.2f", f[k].salario);
		printf("\nNúmero de dependentes: %d", f[k].dependentes);
		return 1;
		}
	if(k==-1){
	printf("\nFuncionário com CPF %s não encontrado", cpf);
	return 0;}
}

void imprimir_funcionarios(struct Funcionario f[], int cont)
{
	if(cont==0){
		printf("\nNão há funcionários registrados");
	}
	for(int i=0; i<cont; i++){
		printf("\n\nNome: %s", f[i].nome);
		printf("\nCPF: %s", f[i].cpf);
		printf("\nCargo: %s", f[i].cargo);
		printf("\nsalário: %.2f", f[i].salario);
		printf("\nNúmero de dependentes: %d", f[i].dependentes);
	}
}

int remover_funcionario(struct Funcionario f[], int *cont, char cpf[])
{
	int k = consultar_cpf(f, *cont, cpf);
	if(k==-1){
		printf("\nFuncionário com CPF %s não encontrado", cpf);
		return 0;
	}
	for(k; k<*cont; k++){
		strcpy(f[k].nome, f[k+1].nome);
		strcpy(f[k].cpf, f[k+1].cpf);
		strcpy(f[k].cargo, f[k+1].cargo);
		f[k].dependentes = f[k+1].dependentes;
		f[k].salario = f[k+1].salario;
	}
	(*cont)--;
	return 1;
}

int alterar_funcionario(struct Funcionario f[], int cont, const char cpf[])
{
	int k = consultar_cpf(f, cont, cpf);
	if(k!=-1){
		printf("\nEntre com o nome do funcionário: ");
		fgets(f[k].nome, sizeof(f[k].nome), stdin);
		f[k].nome[strcspn(f[k].nome, "\n")] = '\0';
		printf("\nEntre com o cargo do funcionário: ");
		fgets(f[k].cargo, sizeof(f[k].cargo), stdin);
		f[k].cargo[strcspn(f[k].cargo, "\n")] = '\0';
		printf("\nEntre com o número de dependentes: ");
		scanf("%d", &f[k].dependentes);
		getchar();
		printf("\nEntre com o salário do funcionário: ");
		scanf("%f", &f[k].salario);
		getchar();
		return 1;
	}else{
		return 0;
	}
}

int menu()
{
	printf("\nMENU PRINCIPAL\n\n");
	printf("\t1. SUBMENU DE FUNCIONÁRIOS\n");
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

int menu_funcionario()
{
	printf("\nMENU DE OPÇÕES DE FUNCIONÁRIOS\n\n");
	printf("\t1. INSERIR UM NOVO FUNCIONÁRIO\n");
	printf("\t2. CONSULTAR DADOS DE UM FUNCIONÁRIO\n");
	printf("\t3. IMPRIMIR TODOS OS FUNCIONÁRIOS\n");
	printf("\t4. EXCLUIR UM FUNCIONÁRIO\n");
	printf("\t5. ALTERAR UM FUNCIONÁRIO\n");
	printf("\t6. RETORNAR AO MENU PRINCIPAL\n");
	printf("\nESCOLHA UMA OPÇÃO: ");
	int opc;
	scanf("%d", &opc);
	getchar();
	return opc;
}

int menu_pesquisa()
{
	printf("\nMENU DE OPÇÕES DE PESQUISA\n\n");
	printf("\t1. INSERIR UMA NOVA PESQUISA\n");
	printf("\t2. CONSULTAR DADOS DE UMA PESQUISA\n");
	printf("\t3. IMMPRIMIR TODAS AS PESQUISAS\n");
	printf("\t4. EXCLUIR UMA PESQUISA\n");
	printf("\t5. ALTERAR UMA PESQUISA\n");
	printf("\t6. RETORNAR AO MENU PRINCIPAL\n");
	printf("\nESCOLHA UMA OPÇÃO: ");
	int opc;
	scanf("%d", &opc);
	getchar();
	return opc;
}

int menu_resposta_pesquisa()
{
	printf("\nMENU DE OPÇÕES DE RESPOSTA DE PESQUISA\n\n");
	printf("\t1. REGISTRAR UMA RESPOSTA\n");
	printf("\t2. CONSULTAR RESPOSTASS DE UMA PESQUISA\n");
	printf("\t3. IMPRIMIR TODAS AS RESPOSTAS\n");
	printf("\t4. ALTERAR UMA RESPOSTA\n");
	printf("\t5. EXCLUIR UMA RESPOSTA\n");
	printf("\t6. RETORNAR AO MENU PRINCIPAL\n");
	printf("\nESCOLHA UMA OPÇÃO: ");
	int opc;
	scanf("%d", &opc);
	getchar();
	return opc;
}

int main()
{
	setlocale(LC_ALL, "Portuguese");
	int capacidade = 50;
	int cont = 0;
	struct Funcionario *vet_funcionario = malloc(capacidade * sizeof(struct Funcionario));	
	if(vet_funcionario== NULL){
		printf("\nErro ao alocar memória");
		return 1;
	}
	int op_menu, op_funcionario, op_pesquisa, op_resposta_pesquisa;
	char cpf[15];
	do{
		op_menu = menu();
		switch(op_menu){
			case 1:{
				do{	
					op_funcionario=menu_funcionario();
					switch (op_funcionario){
						case 1:{
							printf("\nInciando opção inserir");
							if(inserir_funcionario(&vet_funcionario, &cont, &capacidade))
								{printf("\nInserido com sucesso");}
							else{printf("\nNão foi possível inserir");}
							break;
						}
						case 2:{
							printf("\nInciando opção consultar");
							printf("\nEntre com o CPF do funcionário que deseja buscar: ");
							fgets(cpf, sizeof(cpf), stdin);
							cpf[strcspn(cpf, "\n")] = '\0';
							consultar_funcionario(vet_funcionario, cont, cpf);
							break;
						}
						case 3:{
							printf("\nInciando opção imprimir");
							imprimir_funcionarios(vet_funcionario, cont);
							break;
						}
						case 4:{
							printf("\nInciando opção remover");
							printf("\nEntre com o CPF do funcionário que deseja remover: ");
							fgets(cpf, sizeof(cpf), stdin);
							cpf[strcspn(cpf, "\n")] = '\0';
							if(remover_funcionario(vet_funcionario, &cont, cpf)==1){printf("\nRemovido com sucesso!");
							}else{printf("\nNão foi possível remover!");
							}
							break;
						}
						case 5:{
							printf("\nIniciando opção alterar");
							printf("\nEntre com o CPF do funcionário que deseja alterar: ");
							fgets(cpf, sizeof(cpf), stdin);
							cpf[strcspn(cpf, "\n")] = '\0'; 
							if(alterar_funcionario(vet_funcionario, cont, cpf)==1){
								printf("\nAlterado com sucesso!");
							}else{
								printf("\nNão foi possível alterar!");
							}
							break;
						}
						case 6:{
							printf("\nRetornando ao Menu Principal");
							break;
						}
						default:{
							printf("\nOperação inválida");
							break;
						}
					}
				} while(op_funcionario!=6);
				break;
			}
			case 2:{
				do{
					op_pesquisa = menu_pesquisa();
					switch (op_pesquisa)
					{
					case 1:{
						printf("\nInciando opção inserir");
						break;
					}
					case 2:{
						printf("\nIniciando opção consultar");
						break;
					}
					case 3:{
						printf("\nIniciando opção imprimir");
						break;
					}
					case 4:{
						printf("\nInciando opção remover");
						break;
					}
					case 5:{
						printf("\nIniciando opção alterar");
						break;
					}
					case 6:{
						printf("\nRetornando ao Menu Principal");
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
				do{
					op_resposta_pesquisa = menu_resposta_pesquisa();
					switch(op_resposta_pesquisa)
					{
						case 1:{
						printf("\nInciando opção inserir");
						break;
					}
					case 2:{
						printf("\nIniciando opção consultar");
						break;
					}
					case 3:{
						printf("\nIniciando opção imprimir");
						break;
					}
					case 4:{
						printf("\nInciando opção remover");
						break;
					}
					case 5:{
						printf("\nIniciando opção alterar");
						break;
					}
					case 6:{
						printf("\nRetornando ao Menu Principal");
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
		}
	} while(op_menu!=5);

	free(vet_funcionario);
	return 0;
}
