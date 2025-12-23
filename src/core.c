#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../include/andebol.h"

const int MAX_ATLETAS = 15;
const int MAX_NOME_ATLETA = 100;
const int MAX_DESIGNACAO = 100;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Equipa *alocaEquipa(char *designacao, Atleta *atletas, int numAtletas, int capacidadeAtletas) {
    Equipa* novaEquipa = (Equipa*) malloc(sizeof(Equipa));

    if (novaEquipa == NULL) {
        printf("\nERRO: Falha na alocação de memória para a equipa!\n");
        return NULL;
    }

    strcpy(novaEquipa->designacao, designacao);
    novaEquipa->atletas = atletas;
    novaEquipa->numAtletas = numAtletas;
    novaEquipa->capacidadeAtletas = capacidadeAtletas;

    return novaEquipa;
}

Atleta* alocaAtleta(int numIdentificacao, char *nome, int anoNascimento, char *posicao, float mPontos, float mRemates, float mPerdas, float mAssist, float mFintas, int tMinutos, float valia) {
    Atleta* novoAtleta = (Atleta*) malloc(sizeof(Atleta));

    if (novoAtleta == NULL) {
        printf("\nERRO: Falha na alocação de memória para o atleta!\n");
        return NULL;
    }

    novoAtleta->numIdentificacao = numIdentificacao;
    strcpy(novoAtleta->nome, nome);
    novoAtleta->anoNascimento = anoNascimento;
    strcpy(novoAtleta->posicao, posicao);
    novoAtleta->mPontos = mPontos;
    novoAtleta->mRemates = mRemates;
    novoAtleta->mPerdas = mPerdas;
    novoAtleta->mAssist = mAssist;
    novoAtleta->mFintas = mFintas;
    novoAtleta->tMinutos = tMinutos;
    novoAtleta->valia = valia;

    return novoAtleta;
}

Campeonato* alocaCampeonato(char* nome, int ano, int numEquipas, int capacidadeEquipas) {
    Campeonato* novoCampeonato = (Campeonato*) malloc(sizeof(Campeonato));

    if(novoCampeonato == NULL) {
        printf("\nERRO: Falha na alocação de memória para o campeonato!\n");
        free(novoCampeonato);
        return NULL;
    }

    novoCampeonato->equipas = (Equipa*) malloc(capacidadeEquipas * sizeof(Equipa));

    if (novoCampeonato->equipas == NULL) {
        printf("\nERRO: Falha na alocação de memória para as equipas!\n");
        free(novoCampeonato);
        return NULL;
    }
    
    strcpy(novoCampeonato->nome, nome);
    novoCampeonato->ano = ano;
    novoCampeonato->numEquipas = numEquipas;
    novoCampeonato->capacidadeEquipas = capacidadeEquipas;

    return novoCampeonato;
}

void adicionarEquipa(Campeonato *campeonato) {
    int capacidade, numAtletas;
    char designacao[MAX_DESIGNACAO];

    if (campeonato->numEquipas >= campeonato->capacidadeEquipas) {
        int novaCapacidade = campeonato->capacidadeEquipas + 1;
        Equipa* novasEquipas = realloc(campeonato->equipas, novaCapacidade * sizeof(Equipa));

        if (novasEquipas == NULL) {
            printf("\nERRO: Falha na realocação de memória para as equipas!\n");
            return;
        }
        
        campeonato->equipas = novasEquipas;
        campeonato->capacidadeEquipas = novaCapacidade;
        printf("\nINFO: A capacidade de equipas foi aumentada para %d.\n", novaCapacidade);
    }

    printf("\n--- Adicionar Nova Equipa ---\n");
    printf("Introduza a Designação da Equipa: ");
    
    fgets(designacao, sizeof(designacao), stdin);
    designacao[strcspn(designacao, "\n")] = '\0';

    limparBuffer();

    do {
        printf("Qual é a capacidade de atletas da equipa? (1 a %d): ", MAX_ATLETAS);
        scanf("%d", &capacidade);
        limparBuffer();

        printf("Qual é o número de atletas da equipa? (1 a %d): ", MAX_ATLETAS);
        scanf("%d", &numAtletas);
        limparBuffer();

        if (capacidade <= 0 || capacidade > MAX_ATLETAS) {
            printf("Valor inválido! A capacidade deve ser entre 1 e %d.\n", MAX_ATLETAS);
        }
        else if (numAtletas > capacidade) {
            printf("O número de atletas não pode ser maior que a capacidade da equipa.\n");
        }
        else if (numAtletas < 0 || numAtletas > MAX_ATLETAS) {
            printf("O número de atletas deve ser entre 1 e %d.\n", MAX_ATLETAS);
        }
    } while (capacidade <= 0 || capacidade > MAX_ATLETAS || numAtletas > capacidade || numAtletas < 0 || numAtletas > MAX_ATLETAS);

    Atleta* atletas = (Atleta*) malloc(capacidade * sizeof(Atleta));
    if (atletas == NULL) {
        printf("\nERRO: Falha na alocação de memória para os atletas!\n");
        return;
    }

    Equipa* tempEquipa = alocaEquipa(designacao, atletas, numAtletas, capacidade);
    if (tempEquipa == NULL) {
        // A mensagem de erro de alocação de memória está dentro da função alocaEquipa()
        free(atletas);
        return;
    }

    // Copia os dados para o array de equipas do campeonato e liberta a memória temporária
    campeonato->equipas[campeonato->numEquipas] = *tempEquipa;
    free(tempEquipa);

    campeonato->numEquipas++;

    /*
        Local para colocar a função que salva os dados da equipa no ficheiro externo e os devidos tratamentos de erro da mesma
    */

    printf("\nEquipa '%s' adicionada com sucesso!\n", campeonato->equipas[campeonato->numEquipas - 1].designacao);
}

void removerEquipa(Campeonato* campeonato) {
    char designacao[MAX_DESIGNACAO];
    int i, index = -1;

    if (campeonato->numEquipas == 0) {
        printf("\nNenhuma equipa para remover.\n");
        return;
    }

    printf("\n--- Remover Equipa ---\n");
    printf("Introduza a designação da equipa a remover: ");
    fgets(designacao, sizeof(designacao), stdin);
    designacao[strcspn(designacao, "\n")] = '\0';
    limparBuffer();

    for (i = 0; i < campeonato->numEquipas; i++) {
        if (strcmp(campeonato->equipas[i].designacao, designacao) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\nERRO: Equipa '%s' não encontrada.\n", designacao);
        return;
    }

    // Libertar a memória alocada para os atletas da equipa removida
    free(campeonato->equipas[index].atletas);

    // Mover as equipas seguintes para preencher o espaço
    for (i = index; i < campeonato->numEquipas - 1; i++) {
        campeonato->equipas[i] = campeonato->equipas[i + 1];
    }

    campeonato->numEquipas--;

    if (campeonato->numEquipas > 0) {
        Equipa* novasEquipas = realloc(campeonato->equipas, campeonato->numEquipas * sizeof(Equipa));
        if (novasEquipas == NULL) {
            printf("\nERRO: Falha ao tentar diminuir a memória para as equipas!\n");
            // Mesmo que a função realloc falhe, o ponteiro original (campeonato->equipas) ainda é válido.
            // A capacidade permanecerá a mesma de antes.
            return;
        }
        campeonato->equipas = novasEquipas;
        campeonato->capacidadeEquipas = campeonato->numEquipas;
    } else {
        // Se não houver mais equipas, ocorre a libertação de memória do array de equipas
        free(campeonato->equipas);
        campeonato->equipas = NULL;
        campeonato->capacidadeEquipas = 0;
    }

    printf("\nEquipa '%s' removida com sucesso!\n", designacao);
}

int isIdUnico(Campeonato* campeonato, int id) {
    for (int i = 0; i < campeonato->numEquipas; i++) {
        Equipa* equipa = &campeonato->equipas[i];
        for (int j = 0; j < equipa->numAtletas; j++) {
            if (equipa->atletas[j].numIdentificacao == id) {
                return 0; // Não Único
            }
        }
    }
    return 1; // Único
}

void adicionarAtleta(Campeonato *campeonato) {
    int numIdentificacao, anoNascimento, idValido, numEquipa;
    char nome[MAX_NOME_ATLETA], posicao[5];

    for (int i = 0; i < campeonato->numEquipas; i++) {
        printf("\n%d - %s", i + 1, campeonato->equipas[i].designacao);
    }

    printf("A qual equipa deseja adicionar o atleta ? (Escolha o número da equipa que deseja adicionar o atleta)");
    scanf("%d", &numEquipa);
    limparBuffer();

    if (numEquipa <= 0 || &campeonato->equipas[numEquipa - 1] == NULL) {
        printf("\nERRO: Número de equipa inválido!\n");
        return;
    }

    Equipa* equipa = &campeonato->equipas[numEquipa - 1];

    if (equipa->numAtletas >= equipa->capacidadeAtletas) {
        printf("\nERRO: A equipa '%s' atingiu a capacidade máxima de atletas!\n", equipa->designacao);
        return;
    }

    printf("\n--- Adicionar Novo Atleta à Equipa '%s' ---\n", equipa->designacao);

    printf("Introduza o Nome do Atleta: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    limparBuffer(); 

    do {
        idValido = 1; // Inicialmente assume que o ID é válido
        printf("Introduza o Número de Identificação (mínimo 7 dígitos): ");
        scanf("%d", &numIdentificacao);
        limparBuffer();

        if (numIdentificacao < 1000000) {
            printf("ERRO: O número de identificação deve ser um número positivo com no mínimo 7 dígitos.\n");
            idValido = 0;
            continue;
        }

        if (!isIdUnico(campeonato, numIdentificacao)) {
            printf("ERRO: O número de identificação %d já existe.\n", numIdentificacao);
            idValido = 0;
        }

    } while (!idValido); // Repete o ciclo enquanto o utilizador não introduzir um Número de Identificação válido

    printf("Introduza o Ano de Nascimento: ");
    scanf("%d", &anoNascimento);
    limparBuffer();

    do {
        printf("Introduza a Posição (ex: ponta -> pon, lateral -> lat, central -> cen, pivô -> piv, guarda-redes -> gua): ");
        fgets(posicao, sizeof(posicao), stdin);
        posicao[strcspn(posicao, "\n")] = '\0';
        limparBuffer();

        if (strcmp(posicao, "pon") != 0 && strcmp(posicao, "lat") != 0 && strcmp(posicao, "cen") != 0 && strcmp(posicao, "piv") != 0 && strcmp(posicao, "gua") != 0) {
            printf("ERRO: Posição inválida!\n");
            continue;
        }
    } while (strcmp(posicao, "pon") != 0 && strcmp(posicao, "lat") != 0 && strcmp(posicao, "cen") != 0 && strcmp(posicao, "piv") != 0 && strcmp(posicao, "gua") != 0);

    printf("Introduza a média de Pontos: ");
    scanf("%.2f", &equipa->atletas[equipa->numAtletas].mPontos);
    limparBuffer();

    printf("Introduza a média de Remates: ");
    scanf("%.2f", &equipa->atletas[equipa->numAtletas].mRemates);
    limparBuffer();

    printf("Introduza a média de Perdas: ");
    scanf("%.2f", &equipa->atletas[equipa->numAtletas].mPerdas);
    limparBuffer();

    printf("Introduza a média de Assistências: ");
    scanf("%.2f", &equipa->atletas[equipa->numAtletas].mAssist);
    limparBuffer();

    printf("Introduza a média de Fintas: ");
    scanf("%.2f", &equipa->atletas[equipa->numAtletas].mFintas);
    limparBuffer();

    printf("Introduza o número de minutos jogados: ");
    scanf("%d", &equipa->atletas[equipa->numAtletas].tMinutos);
    limparBuffer();

    printf("Calculando valia do Atleta...");
    
    #ifdef _WIN32
	Sleep(3000);
    #else
	sleep(3)
    #endif

    /*
        Local para a função que calcula a valia do jogador com base na sua posição

        Ex: equipa->atletas[equipa->numAtletas].valia = calculaValiaAtleta(<parâmetros da função>)
    */

    Atleta* tempAtleta = alocaAtleta(numIdentificacao, nome, anoNascimento, posicao, equipa->atletas[equipa->numAtletas].mPontos, equipa->atletas[equipa->numAtletas].mRemates, equipa->atletas[equipa->numAtletas].mPerdas, equipa->atletas[equipa->numAtletas].mAssist, equipa->atletas[equipa->numAtletas].mFintas, equipa->atletas[equipa->numAtletas].tMinutos, equipa->atletas[equipa->numAtletas].valia);

    if (tempAtleta == NULL) {
        // A mensagem de erro é imprimida dentro de alocaAtleta
        return;
    }

    // Copia os dados para o array da equipa e liberta a memória temporária
    equipa->atletas[equipa->numAtletas] = *tempAtleta;
    free(tempAtleta);

    equipa->numAtletas++;

    /*
        Local para colocar a função que salva os dados dos atletas na equipa correspondente no ficheiro externo e os devidos tratamentos de erro da mesma
    */

    printf("\nAtleta '%s' adicionado com sucesso à equipa '%s'!\n", equipa->atletas[equipa->numAtletas - 1].nome, equipa->designacao);
}