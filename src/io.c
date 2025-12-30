#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
    #include <windows.h> 
#else
	#include <unistd.h>
#endif
#include <stdbool.h>
#include "../include/andebol.h"

FILE* ficheiro;

void configuracaoInicial(Campeonato* camp);
void carregarDados(Campeonato* camp);
void carregarEquipas(Campeonato* camp);

int dadosExistem;

void ler_ficheiro(Campeonato* camp){
    int f1 = 0, f2 = 0;
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
        //E404
        printf("\n#--------------------------------------------------#");
	    printf("\n|ERRO                                              |");
    	printf("\n|Ficheiro nao existe ou nao encontrado             |");
	    printf("\n|                                                  |");
    	printf("\n| Clicque enter para criar novo ficheiro           |");
	    printf("\n#--------------------------------------------------#");
        dadosExistem = 0;
        getchar();
        configuracaoInicial(camp);
    }
    else if (f1 == 1 && f2 == 1){
        ficheiro = fopen("../data/ini.txt", "w");
        dadosExistem = 0;
        configuracaoInicial(camp);
    }
    else if (f1 == 0 && f2 == 1){
        ficheiro = fopen("../data/ini.txt", "w");
        fprintf(ficheiro, " ");
        carregarDados(camp);
    }
    carregarDados(camp);
}

void imprimirDadosAtleta(Campeonato* campeonato, int numIdentificacao) {
    Atleta* atleta = encontrarAtleta(campeonato, numIdentificacao);
    
    if (atleta == NULL) {
        printf("\nERRO: Atleta não encontrado!\n");
        return;
    }

    printf("\n--- Dados do Atleta ---\11n");
    printf("1. Nome: %s\n", atleta->nome);
    printf("2. Ano de Nascimento: %d\n", atleta->anoNascimento);
    printf("3. Posição: %s\n", atleta->posicao);
    printf("4. Média de Pontos: %.2f\n", atleta->mPontos);
    printf("5. Média de Remates: %.2f\n", atleta->mRemates);
    printf("6. Média de Perdas: %.2f\n", atleta->mPerdas);
    printf("7. Média de Assistências: %.2f\n", atleta->mAssist);
    printf("8. Média de Fintas: %.2f\n", atleta->mFintas);
    printf("9. Número de Minutos Jogados: %d\n", atleta->tMinutos);
    printf("10 Valia do Atleta: %.2f\n", atleta->valia);
    printf("#-------------------------------------#\n");
}

void configuracaoInicial(Campeonato* camp){
    printf("Insira o nome do campeonato:\n");
    scanf("%s", camp->nome);
    printf("Insira o ano:\n");
    scanf("%d", &camp->ano);
    camp->numEquipas = 0;
    printf("Insira o número máximo de equipas:\n");
    scanf("%d", &camp->capacidadeEquipas);
    Campeonato* novo_camp = alocaCampeonato(camp->nome, camp->ano, camp->numEquipas, camp->capacidadeEquipas);
    if (novo_camp){
        *camp = *novo_camp;
        free(novo_camp);
    }
}

void carregarDados(Campeonato* camp){
    char linha[256];
    ficheiro = fopen("../data/equipas.txt", "r");

    fgets(linha, sizeof(linha), ficheiro);
    printf("%s\n", linha);
    char *tok = strtok(linha, "|");
    tok = strtok(NULL, "|");
    strcpy(camp->nome, tok);
    tok = strtok(NULL, "|");
    camp->ano = (int) strtol(tok, NULL, 10);
    tok = strtok(NULL, "|");
    camp->numEquipas = (int) strtol(tok, NULL, 10);
    tok = strtok(NULL, "|");
    camp->capacidadeEquipas = (int) strtol(tok, NULL, 10);
    //
    printf("%s\n", camp->nome);
    printf("%d\n", camp->ano);
    printf("%d\n", camp->numEquipas);
    printf("%d\n", camp->capacidadeEquipas);
    //
    Campeonato* novo_camp = alocaCampeonato(camp->nome, camp->ano, camp->numEquipas, camp->capacidadeEquipas);
    if (novo_camp){
        *camp = *novo_camp;
        free(novo_camp);
    }
    
    carregarEquipas(camp);
}

void carregarEquipas(Campeonato* camp) {
    char linha[256];
    char *endptr;
    
    int i = -1; // Índice da equipa atual (-1 significa nenhuma equipa ativa)
    int j = 0;  // Índice do atleta na equipa atual
    
    // Continuar lendo do ficheiro já aberto
    while (fgets(linha, sizeof(linha), ficheiro)) {
        // Remove nova linha
        linha[strcspn(linha, "\n")] = 0;
        
        if (strlen(linha) == 0) continue;
        
        char *tok = strtok(linha, "|");
        
        if (strcmp(tok, "EQUIPA") == 0) {
            i++;
            j = 0;
            
            // Verificar limites
            if (i >= camp->capacidadeEquipas) {
                printf("Aviso: Número de equipas excede a capacidade!\n");
                break;
            }
            
            tok = strtok(NULL, "|");
            if (tok) strcpy(camp->equipas[i].designacao, tok);
            
            tok = strtok(NULL, "|");
            if (tok) camp->equipas[i].numAtletas = (int)strtol(tok, &endptr, 10);
            
            // Aloca memória para os atletas
            camp->equipas[i].capacidadeAtletas = MAX_ATLETAS;
            camp->equipas[i].atletas = (Atleta*)malloc(MAX_ATLETAS * sizeof(Atleta));
            
            if (camp->equipas[i].atletas == NULL) {
                printf("Erro ao alocar memória para atletas da equipa %s\n", 
                       camp->equipas[i].designacao);
                exit(1);
            }
        }
        else if (strcmp(tok, "ATLETA") == 0) {
            // Verifica se há uma equipa ativa
            if (i == -1) {
                printf("Erro: Atleta sem equipa definida!\n");
                continue;
            }
            
            // Verifica limites de atletas
            if (j >= camp->equipas[i].capacidadeAtletas) {
                printf("Aviso: Número de atletas excede a capacidade na equipa %s!\n",
                       camp->equipas[i].designacao);
                continue;
            }
            
            // Ler todos os campos do atleta
            tok = strtok(NULL, "|");
            if (tok) camp->equipas[i].atletas[j].numIdentificacao = (int)strtol(tok, &endptr, 10);
            
            tok = strtok(NULL, "|");
            if (tok) strcpy(camp->equipas[i].atletas[j].nome, tok);
            
            tok = strtok(NULL, "|");
            if (tok) camp->equipas[i].atletas[j].anoNascimento = (int)strtol(tok, &endptr, 10);
            
            tok = strtok(NULL, "|");
            if (tok) strcpy(camp->equipas[i].atletas[j].posicao, tok);
            
            tok = strtok(NULL, "|");
            if (tok) camp->equipas[i].atletas[j].mPontos = strtof(tok, &endptr);
            
            tok = strtok(NULL, "|");
            if (tok) camp->equipas[i].atletas[j].mRemates = strtof(tok, &endptr);
            
            tok = strtok(NULL, "|");
            if (tok) camp->equipas[i].atletas[j].mPerdas = strtof(tok, &endptr);
            
            tok = strtok(NULL, "|");
            if (tok) camp->equipas[i].atletas[j].mAssist = strtof(tok, &endptr);
            
            tok = strtok(NULL, "|");
            if (tok) camp->equipas[i].atletas[j].mFintas = strtof(tok, &endptr);
            
            tok = strtok(NULL, "|");
            if (tok) camp->equipas[i].atletas[j].tMinutos = (int)strtol(tok, &endptr, 10);
            
            tok = strtok(NULL, "|");
            if (tok) camp->equipas[i].atletas[j].valia = strtof(tok, &endptr);
            
            j++;
        }
    }
    // Atualizar número real de equipas carregadas
    camp->numEquipas = i + 1;
}

void menuA();
void menuB();
void menuAB1(Campeonato* camp);

void pesquisarPor(Campeonato* camp) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    int op;
    int continuar = 1;
    
    while (continuar) {
        printf("\n#--------------------------------------------------#");
        printf("\n| PESQUISAR ATLETAS                                |");
        printf("\n|                                                  |");
        printf("\n| Por Valia___________________________(1)          |");
        printf("\n| Por Ano Exato_______________________(2)          |");
        printf("\n| Por Ano (antes/depois)______________(3)          |");
        printf("\n| Voltar______________________________(0)          |");
        printf("\n#--------------------------------------------------#");
        
        printf("\nQual a sua opção? ");
        scanf("%d", &op);
        limparBuffer();
        
        switch (op) {
            case 1: {
                float valor;
                int maior;
                
                printf("\n--- Pesquisar por Valia ---\n");
                printf("Introduza o valor de referência: ");
                scanf("%f", &valor);
                limparBuffer();
                
                printf("Pretende atletas com valia maior (1) ou menor (0) que %.2f? ", valor);
                scanf("%d", &maior);
                limparBuffer();
                
                pesquisarAtletasPorValia(camp, valor, maior);
                
                printf("\nPressione Enter para continuar...");
                getchar();

                menuAB1(camp);

                break;
            }
            
            case 2: {
                pesquisarAtletasPorAnoExato(camp);
                printf("\nPressione Enter para continuar...");
                getchar();

                menuAB1(camp);

                break;
            }
            
            case 3: {
                int ano, antes;
                
                printf("\n--- Pesquisar por Ano ---\n");
                printf("Introduza o ano de referência: ");
                scanf("%d", &ano);
                limparBuffer();
                
                printf("Pretende atletas nascidos antes (1) ou depois (0) de %d? ", ano);
                scanf("%d", &antes);
                limparBuffer();
                
                pesquisarAtletasPorAno(camp, ano, antes);
                
                printf("\nPressione Enter para continuar...");
                getchar();

                menuAB1(camp);

                break;
            }
            
            case 0: {
                continuar = 0;

                menuAB1(camp);

                break;
            }
            
            default: {
                printf("\nOpção inválida! Tente novamente.\n");
                printf("Pressione Enter para continuar...");
                getchar();

                menuAB1(camp);

                break;
            }
        }
    }
}

void ordenarPor(Campeonato* camp) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    int op;
    int continuar = 1;
    
    while (continuar) {
        printf("\n#--------------------------------------------------#");
        printf("\n| ORDENAR ATLETAS                                  |");
        printf("\n|                                                  |");
        printf("\n| Ordenar por Nome_______________________(1)       |");
        printf("\n| Ordenar por Valia (Crescente)__________(2)       |");
        printf("\n| Ordenar por Valia (Decrescente)________(3)       |");
        printf("\n| Voltar_________________________________(0)       |");
        printf("\n#--------------------------------------------------#");
        
        printf("\nQual a sua opção? ");
        scanf("%d", &op);
        limparBuffer();
        
        switch (op) {
            case 1: {
                int numEquipa;
                
                printf("\n--- Ordenar Atletas por Nome ---\n");
                for (int i = 0; i < camp->numEquipas; i++) {
                    printf("%d. %s\n", i + 1, camp->equipas[i].designacao);
                }
                
                printf("Selecione o número da equipa: ");
                scanf("%d", &numEquipa);
                limparBuffer();
                
                if (numEquipa > 0 && numEquipa <= camp->numEquipas) {
                    ordenarAtletasPorNome(&camp->equipas[numEquipa - 1]);
                    printf("\nAtletas ordenados por nome com sucesso!\n");
                    
                    // Mostrar a lista ordenada
                    listarAtletasEquipaOrdenado(&camp->equipas[numEquipa - 1], 0);
                } else {
                    printf("\nNúmero de equipa inválido!\n");
                }
                
                printf("\nPressione Enter para continuar...");
                getchar();

                menuAB1(camp);

                break;
            }
            
            case 2: {
                int numEquipa;
                
                printf("\n--- Ordenar Atletas por Valia (Crescente) ---\n");
                for (int i = 0; i < camp->numEquipas; i++) {
                    printf("%d. %s\n", i + 1, camp->equipas[i].designacao);
                }
                
                printf("Selecione o número da equipa: ");
                scanf("%d", &numEquipa);
                limparBuffer();
                
                if (numEquipa > 0 && numEquipa <= camp->numEquipas) {
                    ordenarAtletasPorValia(&camp->equipas[numEquipa - 1], 0);
                    printf("\nAtletas ordenados por valia (crescente) com sucesso!\n");
                    
                    // Mostrar a lista ordenada
                    listarAtletasEquipaOrdenado(&camp->equipas[numEquipa - 1], 0);
                } else {
                    printf("\nNúmero de equipa inválido!\n");
                }
                
                printf("\nPressione Enter para continuar...");
                getchar();

                menuAB1(camp);

                break;
            }
            
            case 3: {
                int numEquipa;
                
                printf("\n--- Ordenar Atletas por Valia (Decrescente) ---\n");
                for (int i = 0; i < camp->numEquipas; i++) {
                    printf("%d. %s\n", i + 1, camp->equipas[i].designacao);
                }
                
                printf("Selecione o número da equipa: ");
                scanf("%d", &numEquipa);
                limparBuffer();
                
                if (numEquipa > 0 && numEquipa <= camp->numEquipas) {
                    ordenarAtletasPorValia(&camp->equipas[numEquipa - 1], 1);
                    printf("\nAtletas ordenados por valia (decrescente) com sucesso!\n");
                    
                    // Mostrar a lista ordenada
                    listarAtletasEquipaOrdenado(&camp->equipas[numEquipa - 1], 1);
                } else {
                    printf("\nNúmero de equipa inválido!\n");
                }
                
                printf("\nPressione Enter para continuar...");
                getchar();

                menuAB1(camp);

                break;
            }
            
            case 0: {
                continuar = 0;

                menuAB1(camp);

                break;
            }
            
            default: {
                printf("\nOpção inválida! Tente novamente.\n");
                printf("Pressione Enter para continuar...");
                getchar();

                menuAB1(camp);

                break;
            }
        }
    }
}

void menuMI(Campeonato* camp) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    int MI;
    printf("\n#--------------------------------------------------#");
    printf("\n| MENU PRINCIPAL                                   |");
    printf("\n|                                                  |");
    printf("\n| Ver equipas_______________________________(1)    |");
    printf("\n| Criar nova equipa_________________________(2)    |");
    printf("\n| Apagar equipa_____________________________(3)    |");
    printf("\n| Encontrar equipa mais valiosa_____________(4)    |");
    printf("\n| Encontrar equipa menos valiosa____________(5)    |");
    printf("\n| Apagar todo o registo_____________________(6)    |");
    printf("\n| Gravar registo____________________________(7)    |");
    printf("\n| Atualizar valias de todos os atletas______(8)    |");
    printf("\n| Sair______________________________________(0)    |");
    printf("\n#--------------------------------------------------#");
    
    printf("\nQual a sua opção? ");
    scanf("%d", &MI);
    limparBuffer();
    
    switch (MI) {
        case 1: 
            menuA(camp); 
            break;
        case 2: 
            adicionarEquipa(camp); 
            break;
        case 3: 
            removerEquipa(camp); 
            break;
        case 4: 
            printf("\n--- PROCURANDO EQUIPA MAIS VALIOSA ---\n");
            printf("A analisar todas as equipas...\n");
                
            #ifdef _WIN32
                Sleep(1000);
            #else
                sleep(1);
            #endif
                
            Equipa* equipaMaisValiosa = encontrarEquipaMaisValiosa(camp);
                
            if (equipaMaisValiosa != NULL) {
                float valiaTotal = calcularValiaEquipa(equipaMaisValiosa);
                    
                printf("\n-------------------------------------------------\n");
                printf("      EQUIPA MAIS VALIOSA ENCONTRADA!\n");
                printf("---------------------------------------------------\n");
                printf("Nome: %s\n", equipaMaisValiosa->designacao);
                printf("Número de atletas: %d\n", equipaMaisValiosa->numAtletas);
                printf("Valia total da equipa: %.2f\n", valiaTotal);

            } else {
                printf("\nNenhuma equipa encontrada no campeonato!\n");
                printf("Adicione equipas primeiro.\n");
            }
                
            printf("\nPressione Enter para voltar ao menu principal...");
            getchar();
            menuMI(camp);
            
            break;
        case 5: 
            printf("\n--- PROCURANDO EQUIPA MENOS VALIOSA ---\n");
            printf("A analisar todas as equipas...\n");
                
            #ifdef _WIN32
                    Sleep(1000);
            #else
                sleep(1);
            #endif
                
            Equipa* equipaMenosValiosa = encontrarEquipaMenosValiosa(camp);
                
            if (equipaMenosValiosa != NULL) {
                float valiaTotal = calcularValiaEquipa(equipaMenosValiosa);
                    
                printf("\n-------------------------------------------------\n");
                printf("      EQUIPA MENOS VALIOSA ENCONTRADA!\n");
                printf("---------------------------------------------------\n");
                printf("Nome: %s\n", equipaMenosValiosa->designacao);
                printf("Número de atletas: %d\n", equipaMenosValiosa->numAtletas);
                printf("Valia total da equipa: %.2f\n", valiaTotal);
                
                printf("\nPressione Enter para voltar ao menu principal...");
                getchar();
                menuMI(camp);
            }
            break;
        case 6: 
            ApagarDados(camp); 
            menuMI(camp);
            break;
        case 7: 
            gravarDados(camp);
            printf("\nDados gravados com sucesso!\n");
            printf("Pressione Enter para continuar...");
            getchar();
            menuMI(camp);
            break;
        case 8:
            atualizarTodasValias(camp);
            printf("Pressione Enter para continuar...");
            getchar();
            menuMI(camp);
            break;
        case 0: 
            printf("\nA sair do programa...\n");
            exit(0);
            break;
        default:
            printf("\nOpção inválida!\n");
            printf("Pressione Enter para continuar...");
            getchar();
            menuMI(camp);
            break;
    }
}
int A;
void menuA(Campeonato* camp){ //A
    #ifdef _WIN32
    	system("cls");
	#else
	    system("clear");
    #endif
    if (dadosExistem == 1){
		printf("\n#--------------------------------------------------#");
	    printf("\n|ERRO                                              |");
    	printf("\n|Não existem equipas                               |");
	    printf("\n|                                                  |");
        printf("\n| Clique enter para criar nova equipa             |");
	    printf("\n#--------------------------------------------------#");
        dadosExistem = 0;
        getchar();
        adicionarEquipa(camp);
	}
	else{
        int num[camp->capacidadeEquipas];
        int n = 1;
        for (int i = 0; i < camp->capacidadeEquipas; i++){
            num[i] = n;
            n ++;
        }
        printf("\n#--------------------------------------------------#");
        for (int i = 0; i < camp->numEquipas; i++){
            printf("\n| %s____________________________(%d)       |", camp->equipas[i].designacao, num[i]);      //AB1
        }
	    printf("\n| _________________Voltar________________(0)       |");       //MI
	    printf("\n#--------------------------------------------------#");
	
	    printf("\n Qual a sua opcao ? ");
	    scanf(" %d",&A);
        for (int i = 0; i < camp->numEquipas; i++){
            if (A == num[i]){
                menuAB1(camp);
                printf("%d", A);

            }
            else if (A == 0){
                menuMI(camp);
            }
        }
    }
}

void menuAB1(Campeonato* camp){
    #ifdef _WIN32
		system("cls");
	#else
	    system("clear");
    #endif
    int a = A - 1;
    int AB;
    printf("\n#---------------------------------------------------------------------------------------------------------------------------------------------------------#");
        printf("\n| |número |nome |ano |posição |média de pontos |média de remates |média de perdas |média de assistências |média de fintas |Total de minutos |valia ");
        for (int i = 0; i < camp->equipas[a].numAtletas; i++){
            if (strcmp(camp->equipas[a].atletas[i].posicao, "pon") == 0){
                printf("\n| |%d|%s |%d |ponta       |%.2f |%.2f |%.2f |%.2f |%.2f |%d |%.2f |",camp->equipas[a].atletas[i].numIdentificacao, camp->equipas[a].atletas[i].nome, camp->equipas[a].atletas[i].anoNascimento, camp->equipas[a].atletas[i].mPontos, camp->equipas[a].atletas[i].mRemates, camp->equipas[a].atletas[i].mPerdas, camp->equipas[a].atletas[i].mAssist, camp->equipas[a].atletas[i].mFintas, camp->equipas[a].atletas[i].tMinutos,camp->equipas[a].atletas[i].valia);
            }
            else if (strcmp(camp->equipas[a].atletas[i].posicao, "lat") == 0){
                printf("\n| |%d|%s |%d |lateral     |%.2f |%.2f |%.2f |%.2f |%.2f |%d |%.2f |",camp->equipas[a].atletas[i].numIdentificacao, camp->equipas[a].atletas[i].nome, camp->equipas[a].atletas[i].anoNascimento, camp->equipas[a].atletas[i].mPontos, camp->equipas[a].atletas[i].mRemates, camp->equipas[a].atletas[i].mPerdas, camp->equipas[a].atletas[i].mAssist, camp->equipas[a].atletas[i].mFintas, camp->equipas[a].atletas[i].tMinutos,camp->equipas[a].atletas[i].valia);
            }
            else if (strcmp(camp->equipas[a].atletas[i].posicao, "cen") == 0){
                printf("\n| |%d|%s |%d |central     |%.2f |%.2f |%.2f |%.2f |%.2f |%d |%.2f |",camp->equipas[a].atletas[i].numIdentificacao, camp->equipas[a].atletas[i].nome, camp->equipas[a].atletas[i].anoNascimento, camp->equipas[a].atletas[i].mPontos, camp->equipas[a].atletas[i].mRemates, camp->equipas[a].atletas[i].mPerdas, camp->equipas[a].atletas[i].mAssist, camp->equipas[a].atletas[i].mFintas, camp->equipas[a].atletas[i].tMinutos,camp->equipas[a].atletas[i].valia);
            }
            else if (strcmp(camp->equipas[a].atletas[i].posicao, "piv") == 0){
                printf("\n| |%d|%s |%d |pivô        |%.2f |%.2f |%.2f |%.2f |%.2f |%d |%.2f |",camp->equipas[a].atletas[i].numIdentificacao, camp->equipas[a].atletas[i].nome, camp->equipas[a].atletas[i].anoNascimento, camp->equipas[a].atletas[i].mPontos, camp->equipas[a].atletas[i].mRemates, camp->equipas[a].atletas[i].mPerdas, camp->equipas[a].atletas[i].mAssist, camp->equipas[a].atletas[i].mFintas, camp->equipas[a].atletas[i].tMinutos,camp->equipas[a].atletas[i].valia);
            }
            else if (strcmp(camp->equipas[a].atletas[i].posicao, "gua") == 0){
                printf("\n| |%d|%s |%d |guarda-redes|%.2f |%.2f |%.2f |%.2f |%.2f |%d |%.2f |",camp->equipas[a].atletas[i].numIdentificacao, camp->equipas[a].atletas[i].nome, camp->equipas[a].atletas[i].anoNascimento, camp->equipas[a].atletas[i].mPontos, camp->equipas[a].atletas[i].mRemates, camp->equipas[a].atletas[i].mPerdas, camp->equipas[a].atletas[i].mAssist, camp->equipas[a].atletas[i].mFintas, camp->equipas[a].atletas[i].tMinutos,camp->equipas[a].atletas[i].valia);
            }
        }

        printf("\n|                                                                                                                                                         ");
        printf("\n| Adicionar atleta_______________________(1)                                                                                                              ");		//AC1
        printf("\n| Remover atleta_________________________(2)                                                                                                              ");		//AC2
        printf("\n| Remover todos os atletas_______________(3)                                                                                                              ");     //AC3
        printf("\n| Atualizar atleta_______________________(4)                                                                                                              ");     //AC4
        printf("\n| Encontrar melhor atleta por posição____(5)                                                                                                              ");
        printf("\n| Pesquisar por__________________________(6)                                                                                                              ");
        printf("\n| Ordernar por___________________________(7)                                                                                                              ");		//A
        printf("\n| _________________Voltar________________(8)                                                                                                              ");
        printf("\n| _________________Início________________(0)                                                                                                              ");		//MI
        printf("\n#---------------------------------------------------------------------------------------------------------------------------------------------------------#");

    printf("\nQual a sua opcao? ");
    scanf("%d", &AB);
    limparBuffer();
    
    switch (AB) {
        case 1: 
            adicionarAtleta(camp); 
            menuAB1(camp);
            break;
        case 2: 
            removerAtleta(camp); 
            menuAB1(camp);
            break;
        case 3: 
            removerTodosAtletas(camp); 
            menuAB1(camp);
            break;
        case 4: 
            atualizarAtleta(camp); 
            menuAB1(camp);
            break;
        case 5: 
            encontrarMelhorAtletaPorPosicao(camp);
            printf("\nPressione Enter para continuar...");
            getchar();
            menuAB1(camp);
            break;
        case 6: 
            pesquisarPor(camp);
            menuAB1(camp);
            break;
        case 7: 
            ordenarPor(camp);
            menuAB1(camp);
            break;
        case 8: 
            menuA(camp); 
            break;
        case 0: 
            menuMI(camp); 
            break;
        default:
            printf("\nOpção inválida!\n");
            printf("Pressione Enter para continuar...");
            getchar();
            menuAB1(camp);
            break;
    }
}

void gravarDados(Campeonato* camp) {
    FILE* ficheiro_saida = fopen("../data/equipas.txt", "w");
    
    if (ficheiro_saida == NULL) {
        printf("\nERRO: Nao foi possivel abrir o ficheiro equipas.txt para escrita!\n");
        return;
    }
    
    printf("\nA gravar dados no ficheiro...\n");
    
    fprintf(ficheiro_saida, "CAMPEONATO|%s|%d|%d|%d\n\n", 
            camp->nome, 
            camp->ano, 
            camp->numEquipas, 
            camp->capacidadeEquipas);
    
    // Escrever dados de cada equipa
    for (int i = 0; i < camp->numEquipas; i++) {
        fprintf(ficheiro_saida, "EQUIPA|%s|%d\n", 
                camp->equipas[i].designacao, 
                camp->equipas[i].numAtletas);
        
        // Escrever dados de cada atleta
        for (int j = 0; j < camp->equipas[i].numAtletas; j++) {
            fprintf(ficheiro_saida, 
                    "ATLETA|%d|%s|%d|%s|%.2f|%.2f|%.2f|%.2f|%.2f|%d|%.2f\n",
                    camp->equipas[i].atletas[j].numIdentificacao,
                    camp->equipas[i].atletas[j].nome,
                    camp->equipas[i].atletas[j].anoNascimento,
                    camp->equipas[i].atletas[j].posicao,
                    camp->equipas[i].atletas[j].mPontos,
                    camp->equipas[i].atletas[j].mRemates,
                    camp->equipas[i].atletas[j].mPerdas,
                    camp->equipas[i].atletas[j].mAssist,
                    camp->equipas[i].atletas[j].mFintas,
                    camp->equipas[i].atletas[j].tMinutos,
                    camp->equipas[i].atletas[j].valia);
        }
        
        // Adicionar linha em branco entre equipas (exceto após a última)
        if (i < camp->numEquipas - 1) {
            fprintf(ficheiro_saida, "\n");
        }
    }
    
    // Fechar o arquivo para garantir que os dados são escritos
    fclose(ficheiro_saida);
    
    printf("Dados gravados com sucesso no ficheiro equipas.txt\n");
}