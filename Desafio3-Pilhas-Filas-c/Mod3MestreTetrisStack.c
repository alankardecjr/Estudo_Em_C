#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

typedef struct {
    char nome;
    int id;
} Peca;

// Fila Circular
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int tamanho;
} Fila;

// Pilha
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

// Prototipação
void inicializarFila(Fila *fila);
void inicializarPilha(Pilha *pilha);
Peca gerarPeca();
void enfileirar(Fila *fila, Peca peca);
Peca desenfileirar(Fila *fila);
int filaCheia(Fila *fila);
int filaVazia(Fila *fila);
int pilhaCheia(Pilha *pilha);
int pilhaVazia(Pilha *pilha);
void empilhar(Pilha *pilha, Peca peca);
Peca desempilhar(Pilha *pilha);
void exibirEstado(Fila *fila, Pilha *pilha);
void trocarTopoComFrente(Fila *fila, Pilha *pilha);
void trocaMultipla(Fila *fila, Pilha *pilha);

// Variáveis globais
int idGlobal = 1;
char tiposPeca[] = {'I', 'O', 'T', 'L'};

// Função principal
int main() {
    srand((unsigned) time(NULL));

    Fila fila;
    Pilha pilha;
    int opcao;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Preencher fila inicialmente
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(&fila, gerarPeca());
    }

    do {
        exibirEstado(&fila, &pilha);
        printf("\n--------------------------------------------------");
        printf("\n          ***** Menu de Ações *****\n");
        printf("=>1 - Jogar peça da frente da fila\n");
        printf("=>2 - Enviar peça da fila para a pilha de reserva\n");
        printf("=>3 - Usar peça da pilha de reserva\n");
        printf("=>4 - Trocar frente da fila com topo da pilha\n");
        printf("=>5 - Trocar 3 da fila com 3 da pilha\n");
        printf("=>0 - Sair\n");
        printf("---------------------------------------------------\n");
        printf("\n=>Escolha uma opção: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao) {
            case 1:
                if (!filaVazia(&fila)) {
                    Peca jogada = desenfileirar(&fila);
                    printf("Peça [%c %d] jogada!\n", jogada.nome, jogada.id);
                    enfileirar(&fila, gerarPeca());
                } else {
                    printf("Fila vazia! Não é possível jogar.\n");
                }
                break;

            case 2:
                if (!filaVazia(&fila) && !pilhaCheia(&pilha)) {
                    Peca reservada = desenfileirar(&fila);
                    empilhar(&pilha, reservada);
                    printf("Peça [%c %d] enviada à reserva.\n", reservada.nome, reservada.id);
                    enfileirar(&fila, gerarPeca());
                } else {
                    printf("Erro: Fila vazia ou pilha cheia.\n");
                }
                break;

            case 3:
                if (!pilhaVazia(&pilha)) {
                    Peca usada = desempilhar(&pilha);
                    printf("Peça [%c %d] usada da pilha.\n", usada.nome, usada.id);
                } else {
                    printf("Pilha vazia! Nenhuma peça para usar.\n");
                }
                break;

            case 4:
                trocarTopoComFrente(&fila, &pilha);
                break;

            case 5:
                trocaMultipla(&fila, &pilha);
                break;

            case 0:
                printf("Encerrando o programa.\n");
                break;

            default:
                printf("Opção inválida!\n");
                break;
        }

        printf("\n---------------------------------------------------\n");

    } while (opcao != 0);

    return 0;
}

// Funções auxiliares

void inicializarFila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;
}

void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

Peca gerarPeca() {
    Peca peca;
    peca.nome = tiposPeca[rand() % (sizeof(tiposPeca) / sizeof(char))];
    peca.id = idGlobal++;
    return peca;
}

int filaCheia(Fila *fila) {
    return fila->tamanho == TAM_FILA;
}

int filaVazia(Fila *fila) {
    return fila->tamanho == 0;
}

int pilhaCheia(Pilha *pilha) {
    return pilha->topo == TAM_PILHA - 1;
}

int pilhaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

void enfileirar(Fila *fila, Peca peca) {
    if (filaCheia(fila)) {
        printf("Erro: Fila cheia. Não foi possível enfileirar.\n");
        return;
    }

    fila->itens[fila->fim] = peca;
    fila->fim = (fila->fim + 1) % TAM_FILA;
    fila->tamanho++;
}

Peca desenfileirar(Fila *fila) {
    if (filaVazia(fila)) {
        printf("Erro: Fila vazia. Retorno de peça inválido.\n");
        exit(1);  // Erro crítico
    }

    Peca peca = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % TAM_FILA;
    fila->tamanho--;
    return peca;
}

void empilhar(Pilha *pilha, Peca peca) {
    if (pilhaCheia(pilha)) {
        printf("Erro: Pilha cheia. Não foi possível empilhar.\n");
        return;
    }

    pilha->topo++;
    pilha->itens[pilha->topo] = peca;
}

Peca desempilhar(Pilha *pilha) {
    if (pilhaVazia(pilha)) {
        printf("Erro: Pilha vazia. Retorno de peça inválido.\n");
        exit(1);  // Erro crítico
    }

    Peca peca = pilha->itens[pilha->topo];
    pilha->topo--;
    return peca;
}

void exibirEstado(Fila *fila, Pilha *pilha) {
    printf("\nFila de peças:\t");
    for (int i = 0; i < fila->tamanho; i++) {
        int idx = (fila->inicio + i) % TAM_FILA;
        printf("[%c %d] ", fila->itens[idx].nome, fila->itens[idx].id);
    }

    printf("\nPilha de reserva (topo -> base):\t");
    for (int i = pilha->topo; i >= 0; i--) {
        printf("[%c %d] ", pilha->itens[i].nome, pilha->itens[i].id);
    }
    printf("\n");
}

void trocarTopoComFrente(Fila *fila, Pilha *pilha) {
    if (filaVazia(fila) || pilhaVazia(pilha)) {
        printf("Erro: Não é possível trocar. Fila ou pilha vazia.\n");
        return;
    }

    int idxInicio = fila->inicio;
    int idxTopo = pilha->topo;

    Peca temp = fila->itens[idxInicio];
    fila->itens[idxInicio] = pilha->itens[idxTopo];
    pilha->itens[idxTopo] = temp;

    printf("Troca realizada entre frente da fila e topo da pilha.\n");
}

void trocaMultipla(Fila *fila, Pilha *pilha) {
    if (fila->tamanho < 3 || pilha->topo < 2) {
        printf("Erro: Não há peças suficientes para troca múltipla.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int idxFila = (fila->inicio + i) % TAM_FILA;
        int idxPilha = pilha->topo - i;

        Peca temp = fila->itens[idxFila];
        fila->itens[idxFila] = pilha->itens[idxPilha];
        pilha->itens[idxPilha] = temp;
    }

    printf("Troca múltipla realizada com sucesso.\n");
}
