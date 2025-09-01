#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar uma pessoa
#define MAX 5

// Estrutura de uma pessoa  
typedef struct {
    char nome[30];
    int idade;
} Pessoa;

// Estrutura para pilha de pessoas
typedef struct {
    Pessoa itens[MAX];
    int topo;
} Pilha;

// Funções para manipulação da pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// Funções auxiliares
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX - 1;
}

// Insere uma nova pessoa no topo da pilha
void push(Pilha *p, Pessoa nova) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia. Não é possível inserir.\n");
        return;
    }
 
    p->topo++;
    p->itens[p->topo] = nova;
}

// Remove a pessoa do topo da pilha e copia para o ponteiro fornecido
void pop(Pilha *p, Pessoa *removida) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia. Não é possível remover.\n");
        return;
    }

    *removida = p->itens[p->topo];
    p->topo--;
}

// Consulta a pessoa do topo para o ponteiro fornecido sem removê-la
void peek(Pilha *p, Pessoa *visualizada) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia. Nada para espiar.\n");
        return;
    }

    *visualizada = p->itens[p->topo];
}

// Mostra todos os elementos da pilha
void mostrarPilha(Pilha *p) {
    printf("Pilha (topo -> base):\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%s, %d]\n", p->itens[i].nome, p->itens[i].idade);
    }
    printf("\n");
}

// Exemplo de uso da pilha
int main() {
    Pilha p;
    inicializarPilha(&p);
 
    Pessoa a = {"Ana", 20};
    Pessoa b = {"Bruno", 35};
    Pessoa c = {"Carlos", 28};
 
    push(&p, a);
    push(&p, b);
    push(&p, c);
 
    mostrarPilha(&p);
 
    Pessoa removida;
    pop(&p, &removida);
    printf("Removida: %s, %d\n", removida.nome, removida.idade);
 
    mostrarPilha(&p);
 
    Pessoa topo;
    peek(&p, &topo);
    printf("Topo atual: %s, %d\n", topo.nome, topo.idade);
 
    return 0;
}

