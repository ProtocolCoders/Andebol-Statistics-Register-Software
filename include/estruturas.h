#include "constantes.h"

typedef struct {
    char nome[MAX_NOME_ATLETA];
    int numIdentificacao;
    int anoNascimento;
    char posicao[5];
    float mPontos;
    float mRemates;
    float mPerdas;
    float mAssist;
    float mFintas;
    int tMinutos;
    float valia;
} Atleta;

typedef struct {
    char designacao[MAX_NOME_EQUIPA];
    Atleta* atletas;
    int numAtletas;
    int capacidadeAtletas;
} Equipa;

typedef struct {
    Equipa* equipas;
    int numEquipas;
    int capacidadeEquipas;
} Campeonato;