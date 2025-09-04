#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição do nó da árvore binária de busca (BST)
struct No {
    char valor[50];            // Valor armazenado (string)
    struct No* esquerda;       // Ponteiro para o filho à esquerda
    struct No* direita;        // Ponteiro para o filho à direita
};

// Função para criar um novo nó com o valor fornecido
struct No* criarNo(const char* valor) {
    struct No* novo = (struct No*) malloc(sizeof(struct No));
    strcpy(novo->valor, valor);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Função para inserir um novo valor na árvore
struct No* inserir(struct No* raiz, const char* valor) {
    if (raiz == NULL) 
        return criarNo(valor);
    
    if (strcmp(valor, raiz->valor) < 0)
        raiz->esquerda = inserir(raiz->esquerda, valor);
    else if (strcmp(valor, raiz->valor) > 0)
        raiz->direita = inserir(raiz->direita, valor);
    
    return raiz;
}

// Percurso em ordem (esquerda, raiz, direita)
void emOrdem(struct No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%s ", raiz->valor);
        emOrdem(raiz->direita);
    }
}

// Busca um valor na árvore
int buscar(struct No* raiz, const char* chave) {
    if (raiz == NULL) 
        return 0;

    if (strcmp(chave, raiz->valor) == 0)
        return 1;
    else if (strcmp(chave, raiz->valor) < 0)
        return buscar(raiz->esquerda, chave);
    else
        return buscar(raiz->direita, chave);
}

// Função auxiliar para encontrar o menor valor em uma subárvore
struct No* encontrarMinimo(struct No* raiz) {
    while (raiz->esquerda != NULL)
        raiz = raiz->esquerda;
    return raiz;
}

// Função para remover um valor da árvore
struct No* remover(struct No* raiz, const char* valor) {
    if (raiz == NULL) 
        return NULL;

    if (strcmp(valor, raiz->valor) < 0) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if (strcmp(valor, raiz->valor) > 0) {
        raiz->direita = remover(raiz->direita, valor);
    } else {
        // Caso 1: nó sem filhos
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }

        // Caso 2: nó com apenas um filho
        else if (raiz->esquerda == NULL) {
            struct No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            struct No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Caso 3: nó com dois filhos
        else {
            struct No* sucessor = encontrarMinimo(raiz->direita);
            strcpy(raiz->valor, sucessor->valor);  // Copia o valor do sucessor
            raiz->direita = remover(raiz->direita, sucessor->valor);  // Remove o sucessor
        }
    }

    return raiz;
}

// Função principal
int main() {
    struct No* raiz = NULL;

    // Inserção de valores
    raiz = inserir(raiz, "Pegadas de Lama");
    raiz = inserir(raiz, "Chave perdida");
    raiz = inserir(raiz, "Livro com pagina faltando");
    raiz = inserir(raiz, "Lencol manchado");
    raiz = inserir(raiz, "Gaveta perdida");

    // Impressão em ordem alfabética
    printf("\nElementos em ordem: ");
    emOrdem(raiz);

    // Teste de busca
    printf("\nBusca por 'Lençol manchado': %s", buscar(raiz, "Lencol manchado") ? "Encontrado" : "Não encontrado");
    printf("\nBusca por 'Oculos': %s\n", buscar(raiz, "Oculos") ? "Encontrado" : "Não encontrado");

    return 0;
}
