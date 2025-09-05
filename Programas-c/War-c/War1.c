#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
// Representa um território com nome, cor do exército e quantidade de tropas
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    // Vetor para armazenar até 5 territórios
    Territorio territorios[5];

    printf("Cadastro de Territórios\n");
    printf("=======================\n");

    // Laço para entrada dos dados dos 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);

        // Entrada do nome do território
        printf("Digite o nome do território: ");
        scanf("%29s", territorios[i].nome);

        // Entrada da cor do exército
        printf("Digite a cor do exército: ");
        scanf("%9s", territorios[i].cor);

        // Entrada do número de tropas
        printf("Digite o número de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos dados cadastrados
    printf("\nTerritórios cadastrados:\n");
    printf("=======================\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------\n");
    }

    return 0;
}

