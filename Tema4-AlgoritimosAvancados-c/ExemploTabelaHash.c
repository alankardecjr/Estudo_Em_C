#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 10

// Estrutura de um nó da lista ligada
typedef struct Nodo {
    char nome[50];              // Armazena o nome
    struct Nodo* proximo;       // Ponteiro para o próximo nó
} Nodo;

// A tabela hash é um vetor de ponteiros para Nodo
Nodo* tabela_hash[TAMANHO_TABELA];

// Função hash básica: soma dos valores ASCII dos caracteres
int funcao_hash(const char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TAMANHO_TABELA;
}

// Função de inserção na tabela hash
void inserir(const char* nome) {
    int indice = funcao_hash(nome); // Calcula o índice usando a função hash

    // Cria um novo nó
    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
    if (novo == NULL) {
        printf("Erro de alocação de memória.\n");
        return;
    }

    strcpy(novo->nome, nome);
    novo->proximo = tabela_hash[indice]; // Insere no início da lista encadeada
    tabela_hash[indice] = novo;
}

// Função de busca por nome na tabela hash
Nodo* buscar(const char* nome) {
    int indice = funcao_hash(nome); // Calcula o índice
    Nodo* atual = tabela_hash[indice]; // Percorre a lista nesse índice

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual; // Encontrado
        }
        atual = atual->proximo;
    }

    return NULL; // Não encontrado
}

// Função de remoção de um nome da tabela hash
void remover(const char* nome) {
    int indice = funcao_hash(nome);
    Nodo* atual = tabela_hash[indice];
    Nodo* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            // Remove o nó da lista
            if (anterior == NULL) {
                // O nó a ser removido é o primeiro da lista
                tabela_hash[indice] = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            free(atual);
            printf("'%s' removido.\n", nome);
            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    printf("'%s' não encontrado.\n", nome);
}

// Inicializa a tabela com NULLs
void inicializar_tabela() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela_hash[i] = NULL;
    }
}

// Libera a memória alocada na tabela hash (boa prática)
void liberar_tabela() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Nodo* atual = tabela_hash[i];
        while (atual != NULL) {
            Nodo* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
}

int main() {
    inicializar_tabela(); // Garante que todos os ponteiros começam em NULL

    // Inserções
    inserir("Ana");
    inserir("Bruno");
    inserir("Carlos");
    inserir("Amanda"); // Pode colidir com "Ana"

    // Buscas
    printf("Buscando 'Bruno': %s\n", buscar("Bruno") ? "Encontrado" : "Não encontrado");
    printf("Buscando 'João': %s\n", buscar("João") ? "Encontrado" : "Não encontrado");

    // Remoções
    remover("Carlos");
    remover("João");

    // Liberação de memória
    liberar_tabela();

    return 0;
}
