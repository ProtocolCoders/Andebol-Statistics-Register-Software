#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/andebol.h"


// Valia dos Atletas baseada nas posições e estatísticas
float calcularValiaAtleta(Atleta *a) {
    // Guarda-Redes tem valia 0
    if (strcasecmp(a->posicao, "gua") == 0) return 0.0f;
    // Restantes posições
    /* ponta */
    if (strcasecmp(a->posicao, "pon") == 0) {
        return 5.0f * a->mPontos + 4.0f * a->mRemates + 2.0f * a->mAssist - 3.0f * a->mPerdas;
        /* lateral */
    } else if (strcasecmp(a->posicao, "lat") == 0) {
        return 3.0f * a->mPontos + 2.0f * a->mRemates + 4.0f * a->mAssist - 3.0f * a->mPerdas;
        /* central */
    } else if (strcasecmp(a->posicao, "cen") == 0) {
        return 2.0f * a->mPontos + 5.0f * a->mAssist + 4.0f * a->mFintas - 2.0f * a->mPerdas;
        /* pivo */
    } else if (strcasecmp(a->posicao, "piv") == 0) {
        return 2.0f * a->mPontos + 1.0f * a->mRemates + 5.0f * a->mFintas - 2.0f * a->mPerdas;
    }
    return 0.0f;
}

// Atualiza a valia de todos os atletas no campeonato
void atualizarTodasValias(Campeonato *camp) {
    if (camp == NULL) {
        printf("Erro: Campeonato inválido!\n");
        return;
    }
    if (camp->numEquipas == 0) {
        printf("Aviso: Não há equipas no campeonato.\n");
        return;
    }
    
    for (int i = 0; i < camp->numEquipas; i++) {
        Equipa *e = &camp->equipas[i];
        if (e->atletas == NULL) continue;
        for (int j = 0; j < e->numAtletas; j++) {
            e->atletas[j].valia = calcularValiaAtleta(&e->atletas[j]);
        }
    }
    printf("\nValia dos atletas atualizada com sucesso !\n");
}

//Calcula a valia total de uma equipa através da soma das valias dos seus atletas
float calcularValiaEquipa(Equipa *e) {
    if (e == NULL || e->numAtletas == 0) return 0.0f;
    float soma = 0.0f;
    for (int i = 0; i < e->numAtletas; i++) soma += e->atletas[i].valia;
    return soma;
}

//Ordena atletas por ordem decrescente quando desc = 1 e crescente quando desc = 0 
void ordenarAtletasPorValia(Equipa *e, int desc) {
    if (e == NULL || e->numAtletas <= 1) return;
    int n = e->numAtletas;
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            int cmp = 0;
            if (e->atletas[j].valia < e->atletas[j+1].valia) cmp = -1;
            else if (e->atletas[j].valia > e->atletas[j+1].valia) cmp = 1;
            if ((desc && cmp < 0) || (!desc && cmp > 0)) {
                Atleta tmp = e->atletas[j];
                e->atletas[j] = e->atletas[j+1];
                e->atletas[j+1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

//Ordena atletas pelo nome (alfabeticamente)
void ordenarAtletasPorNome(Equipa *e) {
    if (e == NULL || e->numAtletas <= 1) return;
    int n = e->numAtletas;
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcasecmp(e->atletas[j].nome, e->atletas[j+1].nome) > 0) {
                Atleta tmp = e->atletas[j];
                e->atletas[j] = e->atletas[j+1];
                e->atletas[j+1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

// Lista os atletas de uma equipa ordenados por valia ou por nome
void listarAtletasEquipaOrdenado(Equipa *e, int ordenarPorValiaDesc) {
    if (e == NULL) return;
    if (ordenarPorValiaDesc == 1) ordenarAtletasPorValia(e, 1);
    else ordenarAtletasPorNome(e);

    printf("\n--- Atletas da Equipa: %s ---\n", e->designacao);
    printf("ID | Nome | Ano | Posicao | mPontos | mRemates | mPerdas | mAssist | mFintas | tMinutos | Valia\n");
    for (int i = 0; i < e->numAtletas; i++) {
        Atleta *a = &e->atletas[i];
        /* imprime a lista */
        a->valia = calcularValiaAtleta(a);
        printf("%d | %s | %d | %s | %.1f | %.1f | %.1f | %.1f | %.1f | %d | %.2f\n",
               a->numIdentificacao, a->nome, a->anoNascimento, a->posicao,
               a->mPontos, a->mRemates, a->mPerdas, a->mAssist, a->mFintas, a->tMinutos, a->valia);
    }
}

//Pesquisa atletas por
/* valia (maior ou menor que um valor) */
void pesquisarAtletasPorValia(Campeonato *camp, float valor, int maior) {
    if (camp == NULL) return;
    printf("\n--- Pesquisa Atletas por Valia %s %.2f ---\n", maior ? "maior que" : "menor que", valor);
    for (int i = 0; i < camp->numEquipas; i++) {
        Equipa *e = &camp->equipas[i];
        for (int j = 0; j < e->numAtletas; j++) {
            Atleta *a = &e->atletas[j];
            if ((maior && a->valia > valor) || (!maior && a->valia < valor)) {
                printf("Atleta encontrado: [%s] %d | %s | %s | Valia: %.2f\n", e->designacao, a->numIdentificacao, a->nome, a->posicao, a->valia);
            }
        }
    }
}

/* ano (antes ou depois) */
void pesquisarAtletasPorAno(Campeonato *camp, int ano, int antes) {
    if (camp == NULL) return;
    printf("\n--- Pesquisa Atletas %s %d ---\n", antes ? "nascidos antes de" : "nascidos depois de", ano);
    for (int i = 0; i < camp->numEquipas; i++) {
        Equipa *e = &camp->equipas[i];
        for (int j = 0; j < e->numAtletas; j++) {
            Atleta *a = &e->atletas[j];
            if ((antes && a->anoNascimento < ano) || (!antes && a->anoNascimento > ano)) {
                printf("[%s] %d | %s | Ano: %d | Valia: %.2f\n", e->designacao, a->numIdentificacao, a->nome, a->anoNascimento, a->valia);
            }
        }
    }
}

// Encontra a Equipa com maior valia total/mais valiosa
Equipa* encontrarEquipaMaisValiosa(Campeonato *camp) {
    if (camp == NULL || camp->numEquipas == 0) return NULL;
    Equipa *best = &camp->equipas[0];
    float bestVal = calcularValiaEquipa(best);
    for (int i = 1; i < camp->numEquipas; i++) {
        float v = calcularValiaEquipa(&camp->equipas[i]);
        if (v > bestVal) { bestVal = v; best = &camp->equipas[i]; }
    }
    return best;
}

// Encontra a Equipa com menor valia total/mais valiosa
Equipa* encontrarEquipaMenosValiosa(Campeonato *camp) {
    if (camp == NULL || camp->numEquipas == 0) return NULL;
    Equipa *worst = &camp->equipas[0];
    float worstVal = calcularValiaEquipa(worst);
    for (int i = 1; i < camp->numEquipas; i++) {
        float v = calcularValiaEquipa(&camp->equipas[i]);
        if (v < worstVal) { worstVal = v; worst = &camp->equipas[i]; }
    }
    return worst;
}

// Encontra o melhor Atleta por posição (que tenha mais de 100 minutos de jogo)
void encontrarMelhorAtletaPorPosicao(Campeonato *camp) {
    if (camp == NULL) return;
    const char *posicoes[] = {"pon", "lat", "cen", "piv", "gua"};
    const int np = sizeof(posicoes) / sizeof(posicoes[0]);

    printf("\n--- Melhor Atleta por Posição (min > 100 min) ---\n");
    for (int p = 0; p < np; p++) {
        Atleta *best = NULL;
        float bestVal = -1e30f;
        for (int i = 0; i < camp->numEquipas; i++) {
            Equipa *e = &camp->equipas[i];
            for (int j = 0; j < e->numAtletas; j++) {
                Atleta *a = &e->atletas[j];
                if (a->tMinutos <= 100) continue;
                a->valia = calcularValiaAtleta(a);
                if (strcasecmp(a->posicao, posicoes[p]) == 0) {
                    if (a->valia > bestVal) { bestVal = a->valia; best = a; }
                }
            }
        }
        if (best != NULL) {
            printf("%s: %s (ID %d) - Valia: %.2f - Min: %d\n", posicoes[p], best->nome, best->numIdentificacao, best->valia, best->tMinutos);
        } else {
            printf("%s: (não existe atleta com >100 min)\n", posicoes[p]);
        }
    }
}

// Pesquisa atletas nascidos em um determinado ano
void pesquisarAtletasPorAnoExato(Campeonato *camp) {
    int ano;
    int encontrados = 0;

    if (camp == NULL) {
        printf("Erro: Campeonato inválido!\n");
        return;
    }

    printf("\nIntroduza o ano de nascimento a pesquisar: ");
    scanf("%d", &ano);
    limparBuffer();

    printf("\n--- Pesquisa Atletas Nascidos em %d ---\n", ano);
    for (int i = 0; i < camp->numEquipas; i++) {
        Equipa *e = &camp->equipas[i];
        for (int j = 0; j < e->numAtletas; j++) {
            Atleta *atleta = &e->atletas[j];
            if (atleta->anoNascimento == ano) {
                printf("[%s] %d | %s | Ano: %d | Posição: %s\n", e->designacao, atleta->numIdentificacao, atleta->nome, atleta->anoNascimento, atleta->posicao);
                encontrados++;
            }
        }
    }

    if (encontrados == 0) {
        printf("Nenhum atleta encontrado nascido no ano de %d.\n", ano);
    }
}
