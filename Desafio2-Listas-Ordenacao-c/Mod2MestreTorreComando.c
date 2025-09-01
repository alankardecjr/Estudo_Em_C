#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição do número máximo de componentes
#define MAX_COMPONENTES 20

// Estrutura para representar um componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Contador global de comparações
int comparacoes = 0;

// Mostra os componentes formatadamente
void mostrarComponentes(Componente vet[], int n) {
    printf("\n|===================== < Lista de Componentes > =====================|\n");
    for (int i = 0; i < n; i++) {
        printf("| Nome: %-20s | Tipo: %-15s | Prioridade: %d |\n",
               vet[i].nome, vet[i].tipo, vet[i].prioridade);
    }
    printf("|=====================================================================|\n");
}

// Bubble Sort por nome
void bubbleSortNome(Componente vet[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(vet[j].nome, vet[j + 1].nome) > 0) {
                Componente temp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort por tipo
void insertionSortTipo(Componente vet[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente key = vet[i];
        int j = i - 1;
        while (j >= 0 && (comparacoes++, strcmp(vet[j].tipo, key.tipo) > 0)) {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = key;
    }
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente vet[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (vet[j].prioridade < vet[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            Componente temp = vet[i];
            vet[i] = vet[min];
            vet[min] = temp;
        }
    }
}

// Busca binária por nome
int buscaBinariaPorNome(Componente vet[], int n, char chave[]) {
    int inicio = 0, fim = n - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(vet[meio].nome, chave);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

// Mede o tempo de execução de um algoritmo de ordenação
void medirTempo(void (*algoritmo)(Componente[], int), Componente vet[], int n) {
    clock_t inicio = clock();
    algoritmo(vet, n);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\n=> Comparações: %d\n", comparacoes);
    printf("=> Tempo de execução: %.6f segundos\n", tempo);
}

// Limpa o buffer do teclado (evita erros com fgets após scanf)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função principal
int main() {
    Componente componentes[MAX_COMPONENTES];
    int total = 0;
    int opcao;
    char chave[30];
    int ordenadoPorNome = 0;

    do {
        printf("\n|=========== MENU - TORRE DE FUGA ==========|\n");
        printf("|1. Cadastrar componente                    |\n");
        printf("|2. Ordenar por nome (Bubble Sort)          |\n");
        printf("|3. Ordenar por tipo (Insertion Sort)       |\n");
        printf("|4. Ordenar por prioridade (Selection Sort) |\n");
        printf("|5. Buscar componente-chave (por nome)      |\n");
        printf("|6. Mostrar componentes                     |\n");
        printf("|0. Sair                                    |\n");
        printf("|===========================================|\n");
        printf("\n=> Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            printf("\n*** Entrada inválida. Tente novamente. ***\n");
            limparBuffer();
            continue;
        }
        limparBuffer();
// Processa a opção escolhida
        switch (opcao) {
            case 1:
                if (total < MAX_COMPONENTES) {
                    printf("\n=> Digite o nome do componente: ");
                    fgets(componentes[total].nome, sizeof(componentes[total].nome), stdin);
                    componentes[total].nome[strcspn(componentes[total].nome, "\n")] = '\0';

                    printf("=> Digite o tipo do componente: ");
                    fgets(componentes[total].tipo, sizeof(componentes[total].tipo), stdin);
                    componentes[total].tipo[strcspn(componentes[total].tipo, "\n")] = '\0';

                    do {
                        printf("=> Digite a prioridade (1 a 10): ");
                        if (scanf("%d", &componentes[total].prioridade) != 1) {
                            printf("*** Entrada inválida. Digite um número. ***\n");
                            limparBuffer();
                            continue;
                        }
                        limparBuffer();
                    } while (componentes[total].prioridade < 1 || componentes[total].prioridade > 10);

                    total++;
                } else {
                    printf("\n*** Limite de componentes atingido! ***\n");
                }
                break;

            case 2:
                medirTempo(bubbleSortNome, componentes, total);
                ordenadoPorNome = 1;
                break;

            case 3:
                medirTempo(insertionSortTipo, componentes, total);
                ordenadoPorNome = 0;
                break;

            case 4:
                medirTempo(selectionSortPrioridade, componentes, total);
                ordenadoPorNome = 0;
                break;

            case 5:
                if (!ordenadoPorNome) {
                    printf("\n*** Atenção: Você precisa ordenar por nome antes de buscar! ***\n");
                } else {
                    printf("\n=> Digite o nome do componente-chave: ");
                    fgets(chave, sizeof(chave), stdin);
                    chave[strcspn(chave, "\n")] = '\0';

                    comparacoes = 0;
                    clock_t ini = clock();
                    int pos = buscaBinariaPorNome(componentes, total, chave);
                    clock_t fim = clock();
                    double tempo = (double)(fim - ini) / CLOCKS_PER_SEC;

                    if (pos != -1) {
                        printf("\n=> Componente '%s' encontrado na posição %d!\n", chave, pos);
                    } else {
                        printf("\n=> Componente '%s' não encontrado.\n", chave);
                    }
                    printf("\n=> Comparações: %d\n", comparacoes);
                    printf("=> Tempo de busca: %.6f segundos\n", tempo);
                }
                break;

            case 6:
                mostrarComponentes(componentes, total);
                break;

            case 0:
                printf("\n=> Saindo... Boa sorte na fuga!\n");
                break;

            default:
                printf("\n*** Opção inválida. Tente novamente. ***\n");
        }

    } while (opcao != 0);

    return 0;
}

