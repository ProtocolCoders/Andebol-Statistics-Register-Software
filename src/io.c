#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //sleep
#include <stdbool.h>
#include "../include/andebol.h"


Atleta a, s;
Equipa e, i;
Campeonato c;
FILE* ficheiro;

int ler_ficheiro(){
    Campeonato* equipas;
    char linha[256];
    int compara1, compara2, compara3, contador1 = 0;
    int f1 = 0, f2 = 0, erro;
    ficheiro = fopen("../data/equipas.txt", "r");
    if (ficheiro == NULL){
	    f1 = 1;
    }

    ficheiro = fopen("../data/ini.txt", "r");
    if (ficheiro == NULL){
	    f2 = 1;
    }

    
    if (f1 == 1 && f2 == 0){
        #ifdef _WIN32
    		system("cls");
	    #else
		    system("clear");
        #endif
        //E1
        int E404;
        printf("\n#--------------------------------------------------#");
	    printf("\n|ERRO 404                                          |");
    	printf("\n|Ficheiro nao existe ou nao encontrado             |");
	    printf("\n|                                                  |");
    	printf("\n| Criar novo ficheiro___(1)                        |");
	    printf("\n#--------------------------------------------------#");
        //melhorar isto
        printf("\n Qual a sua opcao ? ");
	    scanf(" %d",&E404);
        erro = 0;
        if (E404 == 1){
            ficheiro = fopen("../data/equipas.txt", "w");
            fprintf(ficheiro, " ");
        }
    }
    else if (f1 == 1 && f2 == 1){
        ficheiro = fopen("../data/equipas.txt", "w");
        fprintf(ficheiro, " ");
        ficheiro = fopen("../data/ini.txt", "w");
        fprintf(ficheiro, " ");
        erro = 0;
    }
    
    else if (f1 == 0 && f2 == 1){
        ficheiro = fopen("../data/ini.txt", "w");
        fprintf(ficheiro, " ");
    }
    if (erro != 0){
        ficheiro = fopen("../data/equipas.txt", "r");
        printf("OK");
        getchar();
        
         while (fgets(linha, sizeof(linha), ficheiro)){
            printf("%s\n", linha);
            char *tok = strtok(linha, "|");
            while (tok != NULL){
                printf("%s\n", tok);
                compara1 = strcmp(tok, "EQUIPA");
                compara2 = strcmp(tok, "ATLETA");
                compara3 = strcmp(tok, "CAMPEONATO");

                if (compara1 == 0 ){
                    tok = strtok(NULL, "|");
                    switch (contador1){
                    case 0: strcpy(e.designacao ,tok); break;
                    case 1: strcpy(i.designacao ,tok); break;
                    }
                    contador1 ++;
                }
                else if (compara2 == 0){
                    tok = strtok(NULL, "|");
                    a.numIdentificacao = (int) strtol(tok, NULL, 10);
                    tok = strtok(NULL, "|");
                    strcpy(a.nome ,tok);
                    tok = strtok(NULL, "|");
                    a.anoNascimento = (int) strtol(tok, NULL, 10);
                    tok = strtok(NULL, "|");
                    strcpy(a.posicao ,tok);
                    tok = strtok(NULL, "|");
                    a.mPontos = strtof(tok, NULL);
                    tok = strtok(NULL, "|");
                    a.mRemates = strtof(tok, NULL);
                    tok = strtok(NULL, "|");
                    a.mPerdas = strtof(tok, NULL);
                    tok = strtok(NULL, "|");
                    a.mAssist = strtof(tok, NULL);
                    tok = strtok(NULL, "|");
                    a.mFintas = strtof(tok, NULL);
                    tok = strtok(NULL, "|");
                    a.tMinutos = (int) strtol(tok, NULL, 10);

                    printf("%d\n",a.numIdentificacao);
                    printf("%s\n",a.nome);
                    printf("%d\n",a.anoNascimento);
                    printf("%s\n",a.posicao);
                    printf("%f\n",a.mPontos);
                    printf("%f\n",a.mRemates);
                    printf("%f\n",a.mPerdas);
                    printf("%f\n",a.mAssist);
                    printf("%f\n",a.mFintas);
                    printf("%d\n",a.tMinutos);
    
                }
                else if (compara3 == 0){
                    tok = strtok(NULL, "|");
                    strcpy(c.nome, tok);
                    tok = strtok(NULL, "|");
                    c.ano = (int) strtol(tok, NULL, 10);
                    tok = strtok(NULL, "|");
                    c.numEquipas = (int) strtol(tok, NULL, 10);
                    tok = strtok(NULL, "|");
                    c.capacidadeEquipas = (int) strtol(tok, NULL, 10);

                    printf("%s\n", c.nome);
                    printf("%d\n", c.ano);
                    printf("%d\n", c.numEquipas);
                    printf("%d\n", c.capacidadeEquipas);
                }
                tok = strtok(NULL, "|");
            }
        }
    }
    
    printf("\n%s",e.designacao);
    printf("\n%s",i.designacao);
    return erro;
}

void menuA();
int menuB(void);

int menuMI(){ //MI
    /*
    if (_WIN32 == true){
		system("cls"); //limpar terminal Windows
	}
	else{
		system("clear"); //limpar terminal Linux/Unix
	} 
    */
    int MI;
	printf("\n#--------------------------------------------------#");
	printf("\n| Ver equipas____________________________(1)       |");		//A
	printf("\n| Criar nova equipa______________________(2)       |");		//AB2
    printf("\n| Apagar equipa__________________________(3)       |");		//AB3
    printf("\n| Apagar registo_________________________(4)       |");		//B
    printf("\n| __________________Sair_________________(5)       |");
	printf("\n#--------------------------------------------------#");
	
	printf("\n Qual a sua opcao ? ");
	scanf(" %d",&MI);
    
	switch (MI){
	case 1: menuA(); break;
	case 2: printf("AB2 inhje");/*função para criar nova equipa*/ break;
	case 3: printf("AB3 bgff");/*função para apagar uma equipa*/ break;
	case 4: menuB(); break;
	case 5: break;
	}
}

void menuA(erro){ //A
    #ifdef _WIN32
    	system("cls");
	#else
	    system("clear");
    #endif
    if (erro == 0){
        int E1;
		printf("\n#--------------------------------------------------#");
	    printf("\n|ERRO 1                                            |");
    	printf("\n|Não existem equipas                               |");
	    printf("\n|                                                  |");
    	printf("\n| Criar nova equipa_____(1)                        |");
	    printf("\n#--------------------------------------------------#");
        //melhorar isto
        if (E1 == 1){
            /*Função para criar equipas*/
        }
	}
	else{
	int A;
    printf("\n#--------------------------------------------------#");
	printf("\n| /*nome da equipa*/_____________________(1)       |");		//AB1
    printf("\n| /*nome da equipa*/_____________________(2)       |");
	printf("\n| _________________Voltar________________(0)       |");       //MI
	printf("\n#--------------------------------------------------#");
	
	printf("\n Qual a sua opcao ? ");
	scanf(" %d",&A);
	switch (A){
	case 1: printf("AB1 dddv"); break;
	case 2: printf("AB1-2 fvfv"); break;
	case 0: menuMI(); break;
	}
    }
}

char menuAB1(){
	
}

char menuAB2(){
	
}

char menuAB3(){
	
}

char menuAC1(){
	
}

char menuAC2(){
	
}

int menuB(){
    /*if (_WIN32 == true){
		system("cls");
	}
	else{
		system("clear");
	}*/
    
    char B;
	printf("\n#--------------------------------------------------#");
	printf("\n|              Tem a certeza que quer              |");
	printf("\n|              apagar todo o registo               |");
	printf("\n|                                                  |");
	printf("\n|                       S/N                        |");
	printf("\n|                                                  |");
	printf("\n|                                                  |");
	printf("\n|                                                  |");
	printf("\n#--------------------------------------------------#");

	printf("\n Qual a sua opcao ? ");
	scanf(" %c",&B);
	switch (B)
	{
	case 'S': printf("kml mdkl")/*função para apagar tudo*/; break;
	case 's': printf("kml mdkl")/*função para apagar tudo*/; break;
	case 'N': menuMI(); break;
	case 'n': menuMI(); break;
	}
}

int main(){
    /*if (_WIN32 == true){
		system("cls");
	}
	else{
		system("clear");
	}*/    
	
	printf("#--------------------------------------------------#\n");
	printf("|                                                  |\n");
	printf("|                                                  |\n");
	printf("|                                                  |\n");
	printf("|         ▄▄▄▄    ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄    ▄▄▄▄▄▄▄       |\n");
	printf("|       ▄██▀▀██▄ █████▀▀▀ ███▀▀███▄ █████▀▀▀       |\n");
	printf("|       ███  ███  ▀████▄  ███▄▄███▀  ▀████▄        |\n");
	printf("|       ███▀▀███    ▀████ ███▀▀██▄     ▀████       |\n");
	printf("|       ███  ███ ███████▀ ███  ▀███ ███████▀       |\n");
	printf("|                                                  |\n");
	printf("|       Andebol Statistics Register Software       |\n");
	printf("|                     V 1.0                        |\n");
	printf("|                                                  |\n");
	printf("|                                                  |\n");
	printf("|                                                  |\n");
	printf("#--------------------------------------------------#\n");
	sleep(2);

    ler_ficheiro();
    menuMI();
}
