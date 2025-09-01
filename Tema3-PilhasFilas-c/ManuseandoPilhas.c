#include <stdio.h>
#include <stdlib.h>

// Estrutura de um elemento da pilha
typedef struct {
    int valor;
} Elemento;

// Estrutura para pilha estática
#define TAMANHO_MAX 100
typedef struct {
    Elemento itens[TAMANHO_MAX];
    int topo;
} Pilha;

// Funções auxiliares
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAMANHO_MAX - 1;
}

// Insere um elemento no topo da pilha
void push(Pilha *p, Elemento e) {
    if (pilhaCheia(p)) {
        printf("Erro: pilha cheia. Não é possível inserir.\n");
        return;
    }
 
    p->topo++;              // Avança o topo
    p->itens[p->topo] = e;  // Insere o novo elemento
}

// Remove e retorna o elemento do topo da pilha
Elemento pop(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Erro: pilha vazia. Não é possível remover.\n");
        exit(EXIT_FAILURE); // Encerra o programa com erro
    }

    Elemento e = p->itens[p->topo]; // Obtém o elemento do topo
    p->topo--;                      // Move o topo para baixo
    return e;                       // Retorna o elemento removido
}

// Retorna o elemento do topo da pilha sem removê-lo
Elemento topo(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Erro: pilha vazia. Não há elemento no topo.\n");
        exit(EXIT_FAILURE); // Encerra o programa com erro
    }

    return p->itens[p->topo];
}

// Copia o elemento do topo para o ponteiro fornecido
void peek(Pilha *p, Elemento *e) {
    if (pilhaVazia(p)) {
        printf("Erro: pilha vazia. Não há elementos no topo.\n");
        e->valor = -1;  // Valor padrão para indicar erro
        return;
    }

    *e = p->itens[p->topo];  // Copia o elemento do topo sem alterar a pilha
}

// Esvazia a pilha (apenas reseta o topo)
void liberarPilha(Pilha *p) {
    p->topo = -1;
}

int main() {
    Pilha minhaPilha;
    minhaPilha.topo = -1; // Inicializa a pilha como vazia

    Elemento e1 = {10};
    Elemento e2 = {20};
    Elemento e3 = {30};

    push(&minhaPilha, e1);
    push(&minhaPilha, e2);
    push(&minhaPilha, e3);

    printf("Elemento no topo: %d\n", topo(&minhaPilha).valor);

    Elemento removido = pop(&minhaPilha);
    printf("Elemento removido: %d\n", removido.valor);

    Elemento peeked;
    peek(&minhaPilha, &peeked);
    if (peeked.valor != -1) {
        printf("Elemento no topo (peek): %d\n", peeked.valor);
    }

    liberarPilha(&minhaPilha);
    if (pilhaVazia(&minhaPilha)) {
        printf("A pilha está vazia após liberar.\n");
    }

    return 0;
}