#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <time.h>

struct Pessoa
{
	char nome[50], cpf[15];
	char data_nasc[15];
	char sexo;
	int cont_tel;
	char telefones[10][15];
	char grau_escolaridade[30];
};

struct Pesquisa{
	char codigo[10];
	char descricao[100];
};

struct RespostaPesquisa{
	char cpf[15];
	char codigoPesquisa[10];
	char data[20];
	char resposta[500];
};

int consultar_cpf(struct Pessoa p[], int cont, const char cpf[])
{
	for(int i=0; i<cont; i++){
		if(strcmp(p[i].cpf, cpf)==0){
		return i;
		}
	}
	return -1;
}

int consultar_codigo(struct Pesquisa p[], int cont, const char codigo[])
{
	for(int i=0; i<cont; i++){
		if(strcmp(p[i].codigo, codigo)==0){
			return i;
		}
	}
	return -1;
}

int consultar_cpf_codigo_resposta(struct RespostaPesquisa rp[], int cont, const char cpf[], const char codigo[]){
	for(int i=0; i<cont; i++){
		if(strcmp(rp[i].cpf, cpf)==0 && strcmp(rp[i].codigoPesquisa, codigo)==0){
			return i;
		}
	}
	return -1;
}


int inserir_pessoas(struct Pessoa **p, int *cont, int *capacidade)
{
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
		printf("\nNão há funcionários registrados");
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

int inserir_pesquisa( struct Pesquisa **p, int *cont, int *capacidade){
	if(*cont>=*capacidade){
		*p = realloc(*p, (*capacidade) * sizeof(struct Pesquisa));
		if(*p==NULL){
			printf("\nERRO AO ALOCAR MEMÓRIA");
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
int inserir_resposta(struct Pessoa **f, struct Pesquisa **p, struct RespostaPesquisa **rp, int *cont_funcionario, int *cont_pesquisa, int *cont_resposta, int *capacidade)
{
	if(*rp==NULL){
		*rp = malloc((*capacidade)*sizeof(struct RespostaPesquisa));
		if(*rp==NULL){
			printf("\nErro ao alocar memória");
			return 0;
		}
	}
	
	if(*cont_resposta>=*capacidade){
		*capacidade *=2;
		*rp = realloc(*rp, (*capacidade) * sizeof(struct RespostaPesquisa));
		if(*rp==NULL){
			printf("\nErro ao realocar memória");
			return 0;
		}
	}
	char cpf[15];
	printf("\nEntre com o cpf: ");
	fgets(cpf, sizeof(cpf), stdin);
	cpf[strcspn(cpf, "\n")] = '\0';
	int k = consultar_cpf(*f, *cont_funcionario, cpf);
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

void mostrar_telefones(struct Pessoa p[], const char cpf[], int cont){
	int k = consultar_cpf(p, cont, cpf);
	if(k!=-1){
		int i =0;
		for(i;i<p[k].cont_tel; i++){
			printf("\nTelefone n° %d da pessoa com o cpf %s: %s", i+1, cpf, p[k].telefones[i]);
		}
	}
	else{printf("\nNão há uma pessoa registrada com esse cpf");}
}

void mostrar_desc_resposta(struct RespostaPesquisa r[], const char codigo[], const char data[], int cont_resposta){
	printf("\nDescrição da pesquisa de codigo %s", codigo);
	int i=0, j=0;;
			
	for(i;i<cont_resposta;i++){
		if(strcmp(r[i].data, data)==0 && strcmp(r[i].codigoPesquisa, codigo)==0){
			printf("\nResposta n° %d da pesquisa: %s", j+1, r[i].resposta);
			j++;
			}
		}
	if(j==0){
		printf("\nNão há uma pesquisa registrada com esse código");
	}
}

struct tm criarStructTm(const char *dataStr){
	struct tm data = {0};
	sscanf(dataStr, "%d/%d/%d", &data.tm_mday, &data.tm_mon, &data.tm_year);
	data.tm_mon -=1;
	data.tm_year -=1900;
	return data;
}

void mostrarPesquisasEntreDatas(time_t inicio, time_t fim, struct RespostaPesquisa *r, int contPesquisa, int contResposta, struct Pesquisa *p){
	printf("\nPesquisas realizadas entre as datas especificadas: ");
	int i=0, j=0;
	for(i;i<contResposta;i++){
		struct tm dataPesquisa = criarStructTm(r[i].data);
		time_t tempoPesquisa = mktime(&dataPesquisa);
		if(tempoPesquisa>=inicio&& tempoPesquisa<=fim){
			for(j;j<contPesquisa;j++){
				if(strcmp(r[i].codigoPesquisa, p[j].codigo)==0){
					printf("Código: %s, Descrição: %s, Data: %s", p[j].codigo, p[j].descricao, r[i].data);
				}
			}
		}
	}
}

void gravarPessoas(struct Pessoa *vet_pessoa, int cont_pessoa){
	FILE *arquivo;
	if((arquivo = fopen("pessoa.dat", "wb"))==NULL){
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
	
	arquivo = fopen("pessoa.dat", "rb");
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

void ler_pesquisa(struct Pesquisa **vet_pesquisa, int *cont_pesquisa, int *capacidade_pesquisa){
	FILE *arquivo;
	long tamanho;
	int n_pesquisa;
	arquivo = fopen("pesquisa.dat", "rb");
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

void ler_resposta(struct RespostaPesquisa **vet_resposta, int *cont_resposta, int *capacidade_resposta){
	FILE *arquivo;
	long tamanho;
	int n_resposta;
	arquivo=fopen("resposta.dat", "rb");
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


void gravar_pesquisa(struct Pesquisa *vet_pesquisa, int cont_pesquisa){
	FILE *arquivo;
	if((arquivo=fopen("pesquisa.dat", "wb"))==NULL){
		printf("\nErro na criação do arquivo");
		exit(0);
	}
	int i=0;
	for(i;i<cont_pesquisa;i++){
		fwrite(&vet_pesquisa[i], sizeof(struct Pesquisa), 1, arquivo);
	}
	fclose(arquivo);
}

void gravar_resposta(struct RespostaPesquisa *vet_resposta, int cont_resposta){
	FILE *arquivo;
	if((arquivo=fopen("resposta.dat", "wb"))==NULL){
		printf("\nErro na criação do arquivo");
		exit(0);
	}
	int i=0;
	for(i;i<cont_resposta;i++){
		fwrite(&vet_resposta[i], sizeof(struct RespostaPesquisa), 1, arquivo);
	}
	fclose(arquivo);
}


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
						printf("\nEntre com o cpf do funcionário que deseja buscar: ");
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
							mostrar_telefones(vet_pessoa, cpf, cont_pessoa);
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
							mostrar_desc_resposta(vet_resposta, codigo_pesquisa, data, cont_resposta);
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
							mostrarPesquisasEntreDatas(inicio, fim , vet_resposta, cont_pesquisa, cont_resposta, vet_pesquisa);
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
