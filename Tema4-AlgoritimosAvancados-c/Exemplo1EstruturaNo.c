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
// FUNÇÕES PARA MANIPULAÇÃO
// ==============================

// Cria um novo nó com o valor especificado
struct No* criarNo(const char* valor) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    if (novoNo != NULL) {
        snprintf(novoNo->valor, sizeof(novoNo->valor), "%s", valor);
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;
    }
    return novoNo;
}

// Calcula a altura da árvore
int altura(struct No* raiz) {
    if (raiz == NULL) 
        return 0;
    int alt_esq = altura(raiz->esquerda);
    int alt_dir = altura(raiz->direita);
    return 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
}

// Calcula a profundidade de um nó específico
int profundidade(struct No* raiz, struct No* alvo, int nivel) {
    if (raiz == NULL) 
        return -1;
    if (raiz == alvo) 
        return nivel;

    int esq = profundidade(raiz->esquerda, alvo, nivel + 1);
    if (esq != -1) 
        return esq;

    return profundidade(raiz->direita, alvo, nivel + 1);
}

// Conta o número de folhas na árvore
int contarFolhas(struct No* raiz) {
    if (raiz == NULL) 
        return 0;
    if (raiz->esquerda == NULL && raiz->direita == NULL) 
        return 1;
    return contarFolhas(raiz->esquerda) + contarFolhas(raiz->direita);
}

// Libera toda a memória alocada pela árvore
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
    // Criando a seguinte árvore binária:
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

    // Altura da árvore
    int alt = altura(raiz);
    printf("Altura da árvore: %d\n", alt);

    // Profundidade do nó "E"
    int prof = profundidade(raiz, raiz->esquerda->direita, 0); // nó "E"
    printf("Profundidade do nó E: %d\n", prof);

    // Número de folhas
    int folhas = contarFolhas(raiz);
    printf("Número de folhas na árvore: %d\n", folhas);

    // Liberar memória
    liberarArvore(raiz);

    return 0;
}
