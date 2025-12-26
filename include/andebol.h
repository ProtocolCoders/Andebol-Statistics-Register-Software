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
    char nome[100];
    int ano;
    Equipa* equipas;
    int numEquipas;
    int capacidadeEquipas;
} Campeonato;

extern const int MAX_ATLETAS;
extern const int MAX_NOME_ATLETA;
extern const int MAX_DESIGNACAO;

void adicionarEquipa(Campeonato *campeonato);

void removerEquipa(Campeonato* campeonato);

void limparBuffer();

Equipa *alocaEquipa(char *designacao, Atleta *atletas, int numAtletas, int capacidadeAtletas);

Atleta* alocaAtleta(int numIdentificacao, char *nome, int anoNascimento, char *posicao, float mPontos, float mRemates, float mPerdas, float mAssist, float mFintas, int tMinutos, float valia);

Campeonato* alocaCampeonato(char* nome, int ano, int numEquipas, int capacidadeEquipas);

void adicionarAtleta(Campeonato *campeonato);

void imprimirDadosAtleta(Campeonato* campeonato, int numIdentificacao);

/* Módulo de Estatísticas */
float calcularValiaAtleta(Atleta *a);
void atualizarTodasValias(Campeonato *camp);
float calcularValiaEquipa(Equipa *e);
void ordenarAtletasPorValia(Equipa *e, int desc);
void ordenarAtletasPorNome(Equipa *e);
void listarAtletasEquipaOrdenado(Equipa *e, int ordenarPorValiaDesc);
void pesquisarAtletasPorValia(Campeonato *camp, float valor, int maior);
void pesquisarAtletasPorAno(Campeonato *camp, int ano, int antes);
Equipa* encontrarEquipaMaisValiosa(Campeonato *camp);
Equipa* encontrarEquipaMenosValiosa(Campeonato *camp);
void encontrarMelhorAtletaPorPosicao(Campeonato *camp);
