#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/andebol.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Função adicionarEquipa()
 * Verifica se há capacidade no campeonato e pede os dados da nova equipa,
 * Aloca memória para a equipa e para os seus atletas e atualiza o número de equipas.
 */

void adicionarEquipa(Campeonato *campeonato) {
    int capacidade;

    if (campeonato->numEquipas >= campeonato->capacidadeEquipas) {
        printf("\nERRO: Capacidade máxima do campeonato atingida! Não é possível adicionar mais equipas.\n");
        return;
    }

    // Ponteiro para a próxima posição livre no array de equipas
    Equipa *novaEquipa = &campeonato->equipas[campeonato->numEquipas - 1];

    printf("\n--- Adicionar Nova Equipa ---\n");
    printf("Introduza a Designação da Equipa: ");
    
    fgets(novaEquipa->designacao, sizeof(novaEquipa->designacao), stdin);
    novaEquipa->designacao[strcspn(novaEquipa->designacao, "\n")] = '\0';

    limparBuffer();

    do {
        printf("Qual é a capacidade de atletas da equipa? (1 a %d): ", MAX_ATLETAS);
        scanf("%d", &capacidade);
        limparBuffer();

        if (capacidade <= 0 || capacidade > MAX_ATLETAS) {
            printf("Valor inválido! A capacidade deve ser entre 1 e %d.\n", MAX_ATLETAS);
        }
    } while (capacidade <= 0 || capacidade > MAX_ATLETAS);

    novaEquipa->capacidadeAtletas = capacidade;
    novaEquipa->numAtletas = 0;

    novaEquipa->atletas = (Atleta*) malloc(novaEquipa->capacidadeAtletas * sizeof(Atleta));

    // Impede a incrementação no número de equipas caso ocorra uma falha na alocação de memória para o array de atletas da estrutura de equipa. A posição será sobreposta na próxima tentativa.
    if (novaEquipa->atletas == NULL) {
        printf("\nERRO: Falha na alocação de memória para os atletas!\n");
        return;
    }

    campeonato->numEquipas++;

    /*
        Local para colocar a função que salva os dados da equipa no ficheiro externo e os devidos tratamentos de erro da mesma
    */

    printf("\nEquipa '%s' adicionada com sucesso!\n", novaEquipa->designacao);
}