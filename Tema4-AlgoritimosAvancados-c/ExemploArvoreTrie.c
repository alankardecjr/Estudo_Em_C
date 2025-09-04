#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAMANHO_ALFABETO 26  // Número de letras do alfabeto em minúsculo

// Estrutura de um nó da Trie
struct NoTrie {
    struct NoTrie* filhos[TAMANHO_ALFABETO]; // Ponteiros para os filhos
    bool ehFimDePalavra;                     // Marca o fim de uma palavra
};

// Cria e inicializa um novo nó da Trie
struct NoTrie* criarNo() { 
    struct NoTrie* novoNo = (struct NoTrie*) malloc(sizeof(struct NoTrie));
    novoNo->ehFimDePalavra = false;
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        novoNo->filhos[i] = NULL;
    }
    return novoNo;
}

// Função para inserir uma palavra na Trie
void inserir(struct NoTrie* raiz, const char* palavra) {
    struct NoTrie* atual = raiz;

    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'a';

        // Garante que o caractere está entre 'a' e 'z'
        if (indice < 0 || indice >= TAMANHO_ALFABETO) continue;

        // Cria o filho se não existir
        if (atual->filhos[indice] == NULL) {
            atual->filhos[indice] = criarNo();
        }

        // Avança para o próximo nível da Trie
        atual = atual->filhos[indice];
    }

    // Marca o fim da palavra
    atual->ehFimDePalavra = true;
}

// Busca uma palavra na Trie
bool buscar(struct NoTrie* raiz, const char* palavra) {
    struct NoTrie* atual = raiz;

    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'a';

        // Garante que o caractere está entre 'a' e 'z'
        if (indice < 0 || indice >= TAMANHO_ALFABETO)
            return false;

        if (atual->filhos[indice] == NULL)
            return false;

        atual = atual->filhos[indice];
    }

    return atual != NULL && atual->ehFimDePalavra;
}

// Lista todas as palavras armazenadas na Trie (em ordem alfabética)
void listarPalavras(struct NoTrie* no, char* buffer, int nivel) {
    if (no->ehFimDePalavra) {
        buffer[nivel] = '\0';
        printf("%s\n", buffer);
    }

    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        if (no->filhos[i] != NULL) {
            buffer[nivel] = 'a' + i;
            listarPalavras(no->filhos[i], buffer, nivel + 1);
        }
    }
}

// Remove acentos, espaços e transforma letras em minúsculas (somente letras de A-Z)
void normalizar(const char* entrada, char* saida) {
    int j = 0;
    for (int i = 0; entrada[i] != '\0'; i++) {
        char c = entrada[i];
        if (c >= 'A' && c <= 'Z') c += 32;  // Converte para minúsculo
        if (c >= 'a' && c <= 'z') saida[j++] = c;  // Mantém apenas letras
    }
    saida[j] = '\0';
}

// Função principal
int main() {
    struct NoTrie* raiz = criarNo(); // Criação da Trie
    char normalizada[100];

    // Inserção de palavras normalizadas
    normalizar("Pegadas de Lama", normalizada);
    inserir(raiz, normalizada);

    normalizar("Chave perdida", normalizada);
    inserir(raiz, normalizada);

    normalizar("Livro com pagina faltando", normalizada);
    inserir(raiz, normalizada);

    normalizar("Lencol manchado", normalizada);
    inserir(raiz, normalizada);

    normalizar("Gaveta perdida", normalizada);
    inserir(raiz, normalizada);

    // Exibe todas as palavras armazenadas
    printf("Palavras na Trie:\n");
    char buffer[100]; // Buffer para formar as palavras durante a listagem
    listarPalavras(raiz, buffer, 0);

    return 0;
}
