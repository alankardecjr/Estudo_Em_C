#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_JOGADORES 1000

typedef struct {
    char nome[50];
    int pontuacao;
} Jogador;

Jogador ranking[MAX_JOGADORES];
int total = 0;

void inserirJogador() {
    if (total >= MAX_JOGADORES) {
        printf("Ranking cheio!\n");
        return;
    }

    Jogador novo;
    printf("Nome: ");
    scanf("%s", novo.nome);
    printf("Pontuação: ");
    scanf("%d", &novo.pontuacao);

    ranking[total++] = novo;
    printf("Jogador inserido com sucesso!\n");
}

void removerJogador() {
    char nome[50];
    printf("Nome do jogador a remover: ");
    scanf("%s", nome);

    for (int i = 0; i < total; i++) {
        if (strcmp(ranking[i].nome, nome) == 0) {
            for (int j = i; j < total - 1; j++) {
                ranking[j] = ranking[j + 1];
            }
            total--;
            printf("Jogador removido!\n");
            return;
        }
    }

    printf("Jogador não encontrado.\n");
}

void exibirRanking() {
    // Ordena por pontuação (simples: bubble sort)
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (ranking[j].pontuacao < ranking[j + 1].pontuacao) {
                Jogador temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }

    printf("\n--- Ranking ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d. %s - %d\n", i + 1, ranking[i].nome, ranking[i].pontuacao);
    }
    printf("----------------\n");
}

void buscaSequencial(char* nome) {
    for (int i = 0; i < total; i++) {
        if (strcmp(ranking[i].nome, nome) == 0) {
            printf("Jogador encontrado: %s com %d pontos\n", ranking[i].nome, ranking[i].pontuacao);
            return;
        }
    }
    printf("Jogador não encontrado.\n");
}

int buscaBinariaRec(int esq, int dir, char* nome) {
    if (esq > dir) return -1;
    int meio = (esq + dir) / 2;
    int cmp = strcmp(ranking[meio].nome, nome);
    if (cmp == 0) return meio;
    if (cmp > 0) return buscaBinariaRec(esq, meio - 1, nome);
    return buscaBinariaRec(meio + 1, dir, nome);
}

void ordenarPorNome() {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (strcmp(ranking[j].nome, ranking[j + 1].nome) > 0) {
                Jogador temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }
}

void menuBuscaBinaria() {
    ordenarPorNome(); // ordena antes de buscar
    char nome[50];
    printf("Nome a buscar: ");
    scanf("%s", nome);
    int pos = buscaBinariaRec(0, total - 1, nome);
    if (pos != -1) {
        printf("Jogador encontrado: %s com %d pontos\n", ranking[pos].nome, ranking[pos].pontuacao);
    } else {
        printf("Jogador não encontrado.\n");
    }
}

int main() {
    int opcao;
    char nomeBusca[50];

    do {
        printf("\n--- Menu ---\n");
        printf("1. Inserir jogador\n");
        printf("2. Remover jogador\n");
        printf("3. Exibir ranking\n");
        printf("4. Buscar jogador (sequencial)\n");
        printf("5. Buscar jogador (binária recursiva)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirJogador(); break;
            case 2: removerJogador(); break;
            case 3: exibirRanking(); break;
            case 4:
                printf("Nome a buscar: ");
                scanf("%s", nomeBusca);
                buscaSequencial(nomeBusca);
                break;
            case 5:
                menuBuscaBinaria();
                break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
