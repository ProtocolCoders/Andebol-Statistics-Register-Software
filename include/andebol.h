typedef struct {
    int numIdentificacao;
    char nome[100];
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

extern const int MAX_ATLETAS;
extern const int MAX_NOME_ATLETA;
extern const int MAX_DESIGNACAO;

void adicionarEquipa(Campeonato *campeonato);

void limparBuffer();

Equipa *alocaEquipa(char *designacao, Atleta *atletas, int numAtletas, int capacidadeAtletas);

Atleta* alocaAtleta(int numIdentificacao, char *nome, int anoNascimento, char *posicao, float mPontos, float mRemates, float mPerdas, float mAssist, float mFintas, int tMinutos, float valia);

Campeonato* alocaCampeonato(int numEquipas, int capacidadeEquipas);