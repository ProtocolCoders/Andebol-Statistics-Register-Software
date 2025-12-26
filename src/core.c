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

    /*
        Local para colocar a função que guarda os dados da aplicação
    */
}

/**
 * Remove um atleta específico de uma equipa com base no numIdentificacao.
 */
void removerAtleta(Campeonato *campeonato) {
    int numId, equipaIndex = -1, atletaIndex = -1;
    char confirmacao;

    if (campeonato == NULL || campeonato->numEquipas == 0) {
        printf("\nNenhuma equipa registada no campeonato.\n");
        return;
    }

    printf("\n--- Remover Atleta ---\n");
    printf("Introduza o Número de Identificação do atleta a remover: ");
    scanf("%d", &numId);
    limparBuffer();

    // Encontrar o atleta e a equipa a que pertence
    for (int i = 0; i < campeonato->numEquipas; i++) {
        for (int j = 0; j < campeonato->equipas[i].numAtletas; j++) {
            if (campeonato->equipas[i].atletas[j].numIdentificacao == numId) {
                equipaIndex = i;
                atletaIndex = j;
                break;
            }
        }
        if (equipaIndex != -1) {
            break;
        }
    }

    if (atletaIndex == -1) {
        printf("\nERRO: Atleta com o número de identificação %d não encontrado.\n", numId);
        return;
    }

    printf("\nAtleta encontrado: %s da equipa %s\n", campeonato->equipas[equipaIndex].atletas[atletaIndex].nome, campeonato->equipas[equipaIndex].designacao);
    printf("Tem a certeza que quer remover este atleta? (S/N): ");
    scanf("%c", &confirmacao);
    limparBuffer();

    if (confirmacao == 'S' || confirmacao == 's') {
        Equipa *equipa = &campeonato->equipas[equipaIndex];
        char nomeAtleta[MAX_NOME_ATLETA];
        strcpy(nomeAtleta, equipa->atletas[atletaIndex].nome);

        // Mover os atletas seguintes para preencher o espaço
        for (int i = atletaIndex; i < equipa->numAtletas - 1; i++) {
            equipa->atletas[i] = equipa->atletas[i + 1];
        }
        equipa->numAtletas--;

        // Realocar a memória para o array de atletas
        if (equipa->numAtletas > 0) {
            Atleta* novosAtletas = realloc(equipa->atletas, equipa->numAtletas * sizeof(Atleta));
            if (novosAtletas == NULL) {
                printf("\nERRO: Falha ao tentar diminuir a memória para os atletas!\n");
            } else {
                equipa->atletas = novosAtletas;
            }
        } else {
            free(equipa->atletas);
            equipa->atletas = NULL;
        }

        printf("\nAtleta '%s' removido com sucesso!\n", nomeAtleta);
    } else {
        printf("\nOperação de remoção cancelada.\n");
    }

    /*
        Local para colocar a função que guarda os dados da aplicação
    */
}

/**
 * Remove todos os atletas de uma equipa.
 */
void removerTodosAtletas(Campeonato* campeonato) {
    int numEquipa;
    char confirmacao;

    if (campeonato == NULL || campeonato->numEquipas == 0) {
        printf("\nNenhuma equipa registada para remover atletas.\n");
        return;
    }

    printf("\n--- Remover Todos os Atletas de uma Equipa ---\n");
    for (int i = 0; i < campeonato->numEquipas; i++) {
        printf("%d - %s\n", i + 1, campeonato->equipas[i].designacao);
    }
    printf("Escolha o número da equipa da qual deseja remover todos os atletas: ");
    scanf("%d", &numEquipa);
    limparBuffer();

    if (numEquipa <= 0 || numEquipa > campeonato->numEquipas) {
        printf("\nERRO: Número de equipa inválido!\n");
        return;
    }

    Equipa* equipa = &campeonato->equipas[numEquipa - 1];

    if (equipa->numAtletas == 0) {
        printf("\nA equipa '%s' já não tem atletas.\n", equipa->designacao);
        return;
    }

    printf("\nTem a certeza que quer remover todos os %d atletas da equipa '%s'? (S/N): ", equipa->numAtletas, equipa->designacao);
    scanf("%c", &confirmacao);
    limparBuffer();

    if (confirmacao == 'S' || confirmacao == 's') {
        free(equipa->atletas);
        equipa->atletas = NULL;
        equipa->numAtletas = 0;
        printf("\nTodos os atletas da equipa '%s' foram removidos com sucesso!\n", equipa->designacao);
    } else {
        printf("\nOperação de remoção cancelada.\n");
    }

    /*
        Local para colocar a função que guarda os dados da aplicação
    */
}

/**
 * Valida se um numId tem 7 dígitos e é único em todas as equipas do campeonato.
 * Retorna 1 se válido, 0 se inválido.
 */
int validarNumId(Campeonato *camp, int numId) {
    if (numId < 1000000 || numId > 9999999) return 0;

    for (int i = 0; i < camp->numEquipas; i++) {
        Equipa *eq = &camp->equipas[i];
        for (int j = 0; j < eq->numAtletas; j++) {
            if (eq->atletas[j].numIdentificacao == numId) return 0;
        }
    }
    return 1;
}

/**
 * Liberta toda a memória alocada para o campeonato e suas equipas.
 */
void libertarMemoria(Campeonato *camp) {
    if (camp == NULL) return;

    for (int i = 0; i < camp->numEquipas; i++) {
        free(camp->equipas[i].atletas);
    }
    free(camp->equipas);
    camp->equipas = NULL;
    camp->numEquipas = 0;
}
