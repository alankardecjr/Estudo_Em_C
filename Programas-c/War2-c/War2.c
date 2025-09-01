#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX_NOME 30
#define MAX_COR 10

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("---Nome do território: %d: ", i+1);
        scanf("%s", mapa[i].nome);
        printf("---Cor do exército: ");
        scanf("%s", mapa[i].cor);
        printf("---Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir territórios
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n******************\n");
    printf("---Territórios---");
    printf("\n******************\n");
    for (int i = 0; i < n; i++) {
        printf("%d %s | Cor: %s | Tropas: %d\n", i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função de ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    int dado_atacante = (rand() % 6) + 1;
    int dado_defensor = (rand() % 6) + 1;
    printf("\nAtaque: %s (%s) [%d tropas] VS %s (%s) [%d tropas]\n", 
        atacante->nome, atacante->cor, atacante->tropas, 
        defensor->nome, defensor->cor, defensor->tropas);
    printf("=== Dado atacante: %d | Dado defensor: %d ===\n", dado_atacante, dado_defensor);

    if (dado_atacante > dado_defensor) {
        printf("=== Atacante venceu! ===\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("=== Defensor resistiu! Atacante perde uma tropa. ===\n");
        if (atacante->tropas > 0) atacante->tropas--;
    }
}

// Função para liberar memória
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    printf("\n***********************************\n");
    printf("=== Bem vindo ao jogo de guerra!===");
    printf("\n***********************************\n");
    srand((unsigned int)time(NULL));
    int n;
    printf("\n***********************************\n");
    printf("-Informe o número de territórios-");
    printf("\n***********************************\n");
    scanf("%d", &n);

    Territorio* mapa = (Territorio*)calloc((size_t)n, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    int atq, def;
    do {
        exibirTerritorios(mapa, n);
        printf("\n*** Escolha um território para atacar (0 para sair): ");
        scanf("%d", &atq);
        if (atq == 0) break;
        printf("*** Escolha um território para defender: ");
        scanf("%d", &def);

        // Validação: não pode atacar território da mesma cor
        if (strcmp(mapa[atq-1].cor, mapa[def-1].cor) == 0) {
            printf("+++ Não é permitido atacar território da mesma cor! +++\n");
            continue;
        }
        atacar(&mapa[atq-1], &mapa[def-1]);
    } while (1);

    liberarMemoria(mapa);
    printf("Memória liberada. Fim do programa.\n");
    return 0;
}