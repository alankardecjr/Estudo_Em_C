#include <stdio.h>
#include <string.h>

// Estrutura que representa um territorio
typedef struct {
    char nome[30];   // Nome do territorio
    char cor[10];    // Cor do exercito
    int tropas;      // Numero de tropas
} Territorio;

// Funcao para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Funcao para cadastrar territorios
void cadastrarTerritorios(Territorio territorios[], int* totalCadastrados) {
    int limite = 5;
    
    if (*totalCadastrados >= limite) {
        printf(">>> Limite de territorios atingido (%d).\n", limite);
        return;
    }

    printf("\n>>> Cadastro de territorios\n");
    printf("===========================\n");

    while (*totalCadastrados < limite) {
        int i = *totalCadastrados;

        printf("\nTerritorio %d:\n", i + 1);

        // Entrada do nome
        printf("Digite o nome do territorio: ");
        scanf("%29s", territorios[i].nome);

        // Entrada da cor do exercito
        printf("Digite a cor do exercito: ");
        scanf("%9s", territorios[i].cor);

        // Entrada do numero de tropas
        printf("Digite o numero de tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBuffer();

        (*totalCadastrados)++;

        // Se ainda ha espaco, pergunta se quer continuar
        if (*totalCadastrados < limite) {
            char opcao;
            printf("Deseja cadastrar outro? (s/n): ");
            scanf(" %c", &opcao);
            limparBuffer();
            if (opcao != 's' && opcao != 'S') {
                break;
            }
        }
    }
}

// Funcao para exibir os territorios cadastrados
void listarTerritorios(Territorio territorios[], int totalCadastrados) {
    if (totalCadastrados == 0) {
        printf(">>> Nenhum territorio cadastrado ainda.\n");
        return;
    }

    printf("\n>>> Territorios cadastrados:\n");
    printf("============================\n");

    for (int i = 0; i < totalCadastrados; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome     : %s\n", territorios[i].nome);
        printf("  Cor      : %s\n", territorios[i].cor);
        printf("  Tropas   : %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }
}

// Funcao principal com menu
int main() {
    Territorio territorios[5];   // Vetor de ate 5 territorios
    int totalCadastrados = 0;    // Contador de cadastros

    char opcao;

    do {
        printf("\n============= MENU =============\n");
        printf("1 - Cadastrar territorios\n");
        printf("2 - Listar territorios\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf(" %c", &opcao);
        limparBuffer();

        switch (opcao) {
            case '1':
                cadastrarTerritorios(territorios, &totalCadastrados);
                break;
            case '2':
                listarTerritorios(territorios, totalCadastrados);
                break;
            case '0':
                printf(">>> Encerrando o programa...\n");
                break;
            default:
                printf(">>> Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != '0');

    return 0;
}
