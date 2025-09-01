#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para usar funções de string (caso precise depois)

// Definição da estrutura para representar uma pessoa
typedef struct {
    char nome[30];
    int idade;
} Pessoa;

// Tamanho máximo da fila
#define MAX 5

// Estrutura da fila circular
typedef struct {
    Pessoa itens[MAX];
    int inicio; // Índice do primeiro elemento
    int fim;    // Índice onde o próximo elemento será inserido
    int total;  // Quantidade atual de elementos na fila
} Fila;

// Inicializa a fila com valores padrão
void inicializaFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;      // Início e fim começam no mesmo ponto
    f->total = 0;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->total == MAX;
}

// Insere uma pessoa na fila
void inserir(Fila *f, Pessoa p) {
    if (filaCheia(f)) {
        printf("Fila cheia. Não é possível inserir.\n");
        return;
    }

    f->itens[f->fim] = p;                  // Insere no índice 'fim'
    f->fim = (f->fim + 1) % MAX;           // Atualiza fim de forma circular
    f->total++;                            // Incrementa total de elementos
}

// Remove uma pessoa da fila e retorna via ponteiro
void remover(Fila *f, Pessoa *p) {
    if (filaVazia(f)) {
        printf("Fila vazia. Não é possível remover.\n");
        return;
    }

    *p = f->itens[f->inicio];              // Recupera o elemento do início
    f->inicio = (f->inicio + 1) % MAX;     // Atualiza início de forma circular
    f->total--;                            // Decrementa total de elementos
}

// Mostra o conteúdo atual da fila
void mostrarFila(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return;
    }

    printf("Fila: ");
    int idx = f->inicio;
    for (int i = 0; i < f->total; i++) {
        printf("[%s, %d] ", f->itens[idx].nome, f->itens[idx].idade);
        idx = (idx + 1) % MAX;             // Avança de forma circular
    }
    printf("\n");
}

int main() {
    Fila fila;
    Pessoa p;
    int opcao;

    inicializaFila(&fila); // Inicializa a fila antes do uso

    do {
        printf("\n========== *Menu* ==========\n");
        printf("=> 1. Inserir pessoa na fila\n");
        printf("=> 2. Remover pessoa da fila\n");
        printf("=> 3. Mostrar fila\n");
        printf("=> 4. Sair\n");
        printf("=============================\n");
        printf("\n#Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado após o scanf

        switch (opcao) {
            case 1:
                if (filaCheia(&fila)) {
                    printf("Fila cheia. Não é possível inserir.\n");
                } else {
                    printf("\nDigite o nome da pessoa: ");
                    fgets(p.nome, sizeof(p.nome), stdin);
                    p.nome[strcspn(p.nome, "\n")] = '\0'; // Remove o '\n' do final
                    printf("Digite a idade da pessoa: ");
                    scanf("%d", &p.idade);
                    getchar(); // Limpa o buffer após ler a idade
                    inserir(&fila, p);
                }
                break;
            case 2:
                if (filaVazia(&fila)) {
                    printf("Fila vazia. Não é possível remover.\n");
                } else {
                    remover(&fila, &p);
                    printf("Pessoa removida: [%s, %d]\n", p.nome, p.idade);
                }
                break;
            case 3:
                mostrarFila(&fila);
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}

