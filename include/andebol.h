typedef struct {
    char nome[100];
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
    char designacao[100];
    Atleta* atletas;
    int numAtletas;
    int capacidadeAtletas;
} Equipa;

typedef struct {
    Equipa* equipas;
    int numEquipas;
    int capacidadeEquipas;
} Campeonato;

const int MAX_ATLETAS = 15;

void adicionarEquipa(Campeonato *campeonato);

void limparBuffer();