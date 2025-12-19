#include "../include/andebol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Remove um atleta de uma equipa com base no numId.
 * Retorna 1 se removido com sucesso, 0 se não encontrado.
 */
int removerAtleta(Equipa *equipa, int numId) {
    if (equipa == NULL || equipa->numAtletas == 0) return 0;

    for (int i = 0; i < equipa->numAtletas; i++) {
        if (equipa->Atletas[i].numId == numId) {
            // Shift dos Atletas seguintes
            for (int j = i; j < equipa->numAtletas - 1; j++) {
                equipa->Atletas[j] = equipa->Atletas[j + 1];
            }
            equipa->numAtletas--;
            equipa->Atletas = realloc(equipa->Atletas, equipa->numAtletas * sizeof(Atleta));
            return 1; // sucesso
        }
    }
    return 0; // não encontrado
}


/**
 * Remove todos os atletas de uma equipa.
 */
void removerTodosAtletas(Equipa *equipa) {
    if (equipa == NULL) return;
    free(equipa->Atletas);
    equipa->Atletas = NULL;
    equipa->numAtletas = 0;
}

/**
 * Valida se um numId tem 7 dígitos e é único em todas as equipas.
 * Retorna 1 se válido, 0 se inválido.
 */
int validarNumId(Equipa *equipas, int numEquipas, int numId) {
    if (numId < 1000000 || numId > 9999999) return 0; // não tem 7 dígitos

    for (int i = 0; i < numEquipas; i++) {
        for (int j = 0; j < equipas[i].numAtletas; j++) {
            if (equipas[i].Atletas[j].numId == numId) return 0; // duplicado
        }
    }
    return 1; // válido
}

/**
 * Liberta toda a memória alocada para equipas e jogadores.
 */
void libertarMemoria(Equipa *equipas, int numEquipas) {
    if (equipas == NULL) return;

    for (int i = 0; i < numEquipas; i++) {
        free(equipas[i].jogadores);
    }
    free(equipas);
}
