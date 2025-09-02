#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==============================
// Definição da estrutura do nó
// ==============================

typedef struct No {
    char valor[50];           // Valor armazenado no nó (nome do ambiente)
    struct No* esquerda;      // Ponteiro para o filho à esquerda
    struct No* direita;       // Ponteiro para o filho à direita
} No;

// ==============================
// Função para criar um novo nó
// ==============================

No* criarNo(char* valor) {
    No* novo = (No*) malloc(sizeof(No));
    if (novo != NULL) {
        strcpy(novo->valor, valor);
        novo->esquerda = NULL;
        novo->direita = NULL;
    }
    return novo;
}

// ==============================
// Função para inserir um valor na árvore (ordem alfabética)
// ==============================

No* inserir(No* raiz, const char* valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }

    if (strcmp(valor, raiz->valor) < 0) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else {
        raiz->direita = inserir(raiz->direita, valor);
    }

    return raiz;
}

// ==============================
// Funções de percurso
// ==============================

void preOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%s ", raiz->valor);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%s ", raiz->valor);
        emOrdem(raiz->direita);
    }
}

void posOrdem(No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%s ", raiz->valor);
    }
}

// ==============================
// Função para liberar memória da árvore
// ==============================

void liberar(No* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esquerda);
        liberar(raiz->direita);
        free(raiz);
    }
}

// ==============================
// Função principal
// ==============================

int main() {
    No* raiz = NULL;

    raiz = inserir(raiz, "Hall de Entrada");
    raiz = inserir(raiz, "Sala de Estar");
    raiz = inserir(raiz, "Biblioteca");
    raiz = inserir(raiz, "Quarto");

    printf("\n                   >>>Execucao do projeto<<<\n");
    printf("\n=============================================================\n");

    printf(">>>Pre ordem: ");
    preOrdem(raiz);
    printf("\n");

    printf(">>>Em ordem: ");
    emOrdem(raiz);
    printf("\n");

    printf(">>>Pos ordem: ");
    posOrdem(raiz);
    printf("\n");

    printf("=============================================================\n");
    printf("\n>>>Criacao da seguinte arvore de ambientes<<<\n");
    printf("\n               Hall de Entrada\n");
    printf("                      |\n");
    printf("              -----------------\n");
    printf("              |               |\n");
    printf("        Sala de Estar    Biblioteca\n");
    printf("              |\n");
    printf("        -------------\n");
    printf("        |           |\n");
    printf("     Quarto        Nulo\n");
    printf("\n>>>Fim<<<\n");

    liberar(raiz);
    return 0;
}
