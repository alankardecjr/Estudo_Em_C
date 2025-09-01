#include <stdio.h>      // Biblioteca para entrada e saída (ex: printf)
#include <stdlib.h>     // Biblioteca para alocação dinâmica (malloc, free)
#include <string.h>     // Biblioteca para manipulação de strings (strcpy)

// ==============================
// Definição da estrutura do nó
// ==============================

struct No {
    char valor[50];           // Valor armazenado no nó (nome do ambiente)
    struct No* esquerda;      // Ponteiro para o filho à esquerda
    struct No* direita;       // Ponteiro para o filho à direita
};

// ==============================
// Função para criar um novo nó
// ==============================

struct No* criarNo(char* valor) {
    struct No* novo = (struct No*) malloc(sizeof(struct No));  // Aloca memória para o novo nó
    strcpy(novo->valor, valor);        // Copia o valor passado para o campo do nó
    novo->esquerda = NULL;             // Inicializa ponteiro da esquerda como NULL
    novo->direita = NULL;              // Inicializa ponteiro da direita como NULL
    return novo;                       // Retorna o novo nó criado
}

// ==============================
// Função de percurso em PRÉ-ORDEM
// Visita: raiz → esquerda → direita
// ==============================

void preOrdem(struct No* raiz) {
    if (raiz != NULL) {
        printf("%s ", raiz->valor);       // Visita a raiz
        preOrdem(raiz->esquerda);         // Percorre subárvore esquerda
        preOrdem(raiz->direita);          // Percorre subárvore direita
    }
}

// ==============================
// Função de percurso EM ORDEM
// Visita: esquerda → raiz → direita
// ==============================

void emOrdem(struct No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);          // Percorre subárvore esquerda
        printf("%s ", raiz->valor);       // Visita a raiz
        emOrdem(raiz->direita);           // Percorre subárvore direita
    }
}

// ==============================
// Função de percurso em PÓS-ORDEM
// Visita: esquerda → direita → raiz
// ==============================

void posOrdem(struct No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);         // Percorre subárvore esquerda
        posOrdem(raiz->direita);          // Percorre subárvore direita
        printf("%s ", raiz->valor);       // Visita a raiz
    }
}

// ==============================
// Função para liberar memória da árvore
// ==============================

void liberar(struct No* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esquerda);          // Libera subárvore esquerda
        liberar(raiz->direita);           // Libera subárvore direita
        free(raiz);                       // Libera o nó atual
    }
}

// ==============================
// Função principal
// ==============================

int main() {
    // Criação da seguinte árvore de ambientes:
    //
    //        Hall de Entrada
    //         /           \
    //  Sala de Estar    Biblioteca
    //     /
    //  Quarto

    struct No* raiz = criarNo("Hall de Entrada");
    raiz->esquerda = criarNo("Sala de Estar");
    raiz->direita = criarNo("Biblioteca");
    raiz->esquerda->esquerda = criarNo("Quarto");

    // Exibe os três tipos de percurso

    printf("Pré-ordem: ");
    preOrdem(raiz);       // Deve exibir: Hall de Entrada, Sala de Estar, Quarto, Biblioteca
    printf("\n");

    printf("Em ordem: ");
    emOrdem(raiz);        // Deve exibir: Quarto, Sala de Estar, Hall de Entrada, Biblioteca
    printf("\n");

    printf("Pós-ordem: ");
    posOrdem(raiz);       // Deve exibir: Quarto, Sala de Estar, Biblioteca, Hall de Entrada
    printf("\n");

    liberar(raiz);        // Libera a memória alocada
    return 0;
}
// ==============================================
// Fim do código
