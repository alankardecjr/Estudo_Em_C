#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==============================
// ESTRUTURA DO NÓ DA ÁRVORE
// ==============================
struct No {
    char valor[50];
    struct No* esquerda;
    struct No* direita;
};

// ==============================
// FUNÇÕES DE PERCURSO
// ==============================

// Visita: raiz → esquerda → direita
void preOrdem(struct No* raiz) {
    if (raiz != NULL) {
        printf("%s ", raiz->valor);             // Visita a raiz
        preOrdem(raiz->esquerda);               // Visita subárvore esquerda
        preOrdem(raiz->direita);                // Visita subárvore direita
    }
}

// Visita: esquerda → raiz → direita
void emOrdem(struct No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);                // Visita subárvore esquerda
        printf("%s ", raiz->valor);             // Visita a raiz
        emOrdem(raiz->direita);                 // Visita subárvore direita
    }
}

// Visita: esquerda → direita → raiz
void posOrdem(struct No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);               // Visita subárvore esquerda
        posOrdem(raiz->direita);                // Visita subárvore direita
        printf("%s ", raiz->valor);             // Visita a raiz
    }
}

// ==============================
// FUNÇÕES AUXILIARES
// ==============================

// Cria um novo nó
struct No* criarNo(const char* valor) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    if (novoNo != NULL) {
        snprintf(novoNo->valor, sizeof(novoNo->valor), "%s", valor);
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;
    }
    return novoNo;
}

// Libera memória da árvore
void liberarArvore(struct No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

// ==============================
// FUNÇÃO PRINCIPAL (main)
// ==============================
int main() {
    // Exemplo de árvore binária:
    //
    //         A
    //       /   \
    //      B     C
    //     / \   / \
    //    D   E F   G

    struct No* raiz = criarNo("A");
    raiz->esquerda = criarNo("B");
    raiz->direita = criarNo("C");
    raiz->esquerda->esquerda = criarNo("D");
    raiz->esquerda->direita = criarNo("E");
    raiz->direita->esquerda = criarNo("F");
    raiz->direita->direita = criarNo("G");

    printf("Percurso em Pré-Ordem: ");
    preOrdem(raiz);
    printf("\n");

    printf("Percurso em Em-Ordem: ");
    emOrdem(raiz);
    printf("\n");

    printf("Percurso em Pós-Ordem: ");
    posOrdem(raiz);
    printf("\n");

    liberarArvore(raiz);
    return 0;
}
