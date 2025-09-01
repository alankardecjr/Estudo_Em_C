#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define TAM_FILA 5     // Tamanho fixo da fila circular
#define TAM_PILHA 3    // Capacidade máxima da pilha

// Estrutura da Peça
typedef struct {
    char nome;  // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;     // Identificador único
} Peca;

// Fila Circular
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int tamanho;
} Fila;

// Pilha de Reserva
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

// Funções Globais
int contadorID = 0;  // Usado para gerar IDs únicos

char tiposPeca[] = {'I', 'O', 'T', 'L'}; // Tipos possíveis de peças

// Gera uma nova peça com tipo aleatório e ID único
Peca gerarPeca() {
    Peca nova;
    nova.nome = tiposPeca[rand() % 4];
    nova.id = contadorID++;
    return nova;
}

// Inicializações
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;

    // Preenche a fila com peças iniciais
    for (int i = 0; i < TAM_FILA; i++) {
        f->itens[f->fim] = gerarPeca();
        f->fim = (f->fim + 1) % TAM_FILA;
        f->tamanho++;
    }
}

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// Operações com Fila
int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

int filaCheia(Fila *f) {
    return f->tamanho == TAM_FILA;
}

// Remove a peça da frente da fila
Peca jogarPeca(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila está vazia!\n");
        Peca erro = {'-', -1};
        return erro;
    }

    Peca p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->tamanho--;

    // Gera e insere nova peça no fim
    f->itens[f->fim] = gerarPeca();
    f->fim = (f->fim + 1) % TAM_FILA;
    f->tamanho++;

    return p;
}

// Move a peça da frente da fila para a pilha de reserva
int reservarPeca(Fila *f, Pilha *p) {
    setlocale(LC_ALL, "pt_BR.UTF-8");       
    if (filaVazia(f)) {
        printf("Fila vazia. Não é possível reservar.\n");
        return 0;
    }

    if (p->topo == TAM_PILHA - 1) {
        printf("Pilha cheia. Não é possível reservar mais peças.\n");
        return 0;
    }

    // Remove da fila
    Peca pecaReservada = jogarPeca(f);

    // Coloca na pilha
    p->topo++;
    p->itens[p->topo] = pecaReservada;
    return 1;
}

// Remove a peça do topo da pilha
Peca usarReservada(Pilha *p) {
    if (p->topo == -1) {
        printf("Pilha vazia. Nenhuma peça reservada.\n");
        Peca erro = {'-', -1};
        return erro;
    }

    Peca usada = p->itens[p->topo];
    p->topo--;
    return usada;
}

// Exibir Estado Atual
void exibirEstado(Fila *f, Pilha *p) {
    printf("\nEstado atual:\n");

    // Exibir fila
    printf("Fila de peças:\t");
    int i = f->inicio;
    for (int count = 0; count < f->tamanho; count++) {
        Peca peca = f->itens[i];
        printf("[%c %d] ", peca.nome, peca.id);
        i = (i + 1) % TAM_FILA;
    }

    // Exibir pilha
    printf("\nPilha de reserva\t(Topo -> Base): ");
    for (int i = p->topo; i >= 0; i--) {
        Peca peca = p->itens[i];
        printf("[%c %d] ", peca.nome, peca.id);
    }
    printf("\n");
}

// Menu
void exibirMenu() {
    printf("\n======================================\n");
    printf("|======== Opções de Ação ========|\n");
    printf("======================================\n");
    printf("=>1\tJogar peça\n");
    printf("=>2\tReservar peça\n");
    printf("=>3\tUsar peça reservada\n");
    printf("=>0\tSair\n");
    printf("======================================\n");
    printf("\n=>Opção: ");
}

// Função Principal
int main() {
    srand(time(NULL)); // Inicializa gerador de números aleatórios

    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int opcao;

    do {
        exibirEstado(&fila, &pilha);
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca jogada = jogarPeca(&fila);
                printf("Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
                break;
            }
            case 2: {
                if (reservarPeca(&fila, &pilha)) {
                    printf("Peça reservada com sucesso.\n");
                }
                break;
            }
            case 3: {
                Peca usada = usarReservada(&pilha);
                if (usada.id != -1)
                    printf("Peça usada da reserva: [%c %d]\n", usada.nome, usada.id);
                break;
            }
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

