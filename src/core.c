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

Campeonato* alocaCampeonato(int numEquipas, int capacidadeEquipas) {
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
    
    novoCampeonato->numEquipas = numEquipas;
    novoCampeonato->capacidadeEquipas = capacidadeEquipas;

    return novoCampeonato;
}

/* Função adicionarEquipa()
 * Verifica se há capacidade no campeonato e pede os dados da nova equipa,
 * Aloca memória para a equipa e para os seus atletas e atualiza o número de equipas.
 */

void adicionarEquipa(Campeonato *campeonato) {
    int capacidade, numAtletas;
    char designacao[MAX_DESIGNACAO];

    if (campeonato->numEquipas >= campeonato->capacidadeEquipas) {
        printf("\nERRO: Capacidade máxima do campeonato atingida! Não é possível adicionar mais equipas.\n");
        return;
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