#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 10
typedef struct {
    char nome[50];
    int ocupado; // 0 = vazio, 1 = ocupado, -1 = removido
} Entrada;

Entrada tabela_hash[TAMANHO_TABELA];

int funcao_hash(const char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TAMANHO_TABELA;
}

void inserir(const char* nome) { 
    int indice = funcao_hash(nome);
    for (int i = 0; i < TAMANHO_TABELA; i++) {
                int pos = (indice + i) % TAMANHO_TABELA;
        
                if (tabela_hash[pos].ocupado == 0 || tabela_hash[pos].ocupado == -1) {
                    strcpy(tabela_hash[pos].nome, nome);
                    tabela_hash[pos].ocupado = 1;
                    return;
            }
    }
        printf("Tabela cheia. Não foi possível inserir '%s'.\n", nome);
}

int buscar(const char* nome) { 
    int indice = funcao_hash(nome);
    
        for (int i = 0; i < TAMANHO_TABELA; i++) {
                int pos = (indice + i) % TAMANHO_TABELA;
        
                if (tabela_hash[pos].ocupado == 0) {
                    return -1; // Paramos: posição nunca foi usada
            }
    
            if (tabela_hash[pos].ocupado == 1 && strcmp(tabela_hash[pos].nome, nome) == 0) {
                    return pos;
            }
    }
    
        return -1; // Não encontrou
}

void remover(const char* nome) {
    int pos = buscar(nome);
    if (pos == -1) {
        printf("'%s' não encontrado.\n", nome);
        return;
    }
 
    tabela_hash[pos].ocupado = -1;
    printf("'%s' removido da tabela.\n", nome);
}

int main() {
    // Inicializa a tabela
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela_hash[i].ocupado = 0;
    }
 
    inserir("Ana");
    inserir("Bruno");
    inserir("Carlos");
    inserir("Amanda"); // Pode colidir com Ana
 
    printf("Buscando 'Bruno': %s\n", buscar("Bruno") != -1 ? "Encontrado" : "Não encontrado");
    printf("Buscando 'João': %s\n", buscar("João") != -1 ? "Encontrado" : "Não encontrado");
 
    remover("Carlos");
    remover("João");
 
    return 0;
}