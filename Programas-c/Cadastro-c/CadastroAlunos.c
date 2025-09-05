#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 5
#define MAX_STR 100

// Estrutura que representa um aluno
typedef struct {
    char nome[MAX_STR];
    int matricula;
    float nota;
} Aluno;

// Função para limpar o buffer do teclado (evita problemas com fgets e scanf)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para cadastrar um novo aluno
void cadastrarAluno(Aluno alunos[], int* qtdAlunos) {
    if (*qtdAlunos >= MAX_ALUNOS) {
        printf(">>> Limite de alunos atingido! (%d)\n", MAX_ALUNOS);
        return;
    }

    Aluno novo;

    printf(">>> Nome do aluno: ");
    fgets(novo.nome, MAX_STR, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // Remove o \n do final

    printf(">>> Matricula: ");
    scanf("%d", &novo.matricula);
    
    printf(">>> Nota: ");
    scanf("%f", &novo.nota);
    limparBuffer();

    // Adiciona o novo aluno no array
    alunos[*qtdAlunos] = novo;
    (*qtdAlunos)++;

    printf(">>> Aluno cadastrado com sucesso!\n");
}

// Função para listar os alunos cadastrados
void listarAlunos(Aluno alunos[], int qtdAlunos) {
    if (qtdAlunos == 0) {
        printf(">>> Nenhum aluno cadastrado ainda.\n");
        return;
    }

    printf("\n================== LISTA DE ALUNOS ==================\n");
    for (int i = 0; i < qtdAlunos; i++) {
        printf("Aluno %d:\n", i + 1);
        printf("  Nome     : %s\n", alunos[i].nome);
        printf("  Matricula: %d\n", alunos[i].matricula);
        printf("  Nota     : %.2f\n", alunos[i].nota);
        printf("-----------------------------------------------------\n");
    }
}

// Função principal com menu
int main() {
    Aluno alunos[MAX_ALUNOS];  // Vetor de alunos
    int qtdAlunos = 0;         // Contador de alunos cadastrados
    char opcao;

    do {
        printf("\n================= MENU =================\n");
        printf(" (1) Cadastrar aluno\n");
        printf(" (2) Listar alunos\n");
        printf(" (0) Sair\n");
        printf(">>> Escolha uma opcao: ");
        scanf(" %c", &opcao);
        limparBuffer();

        switch (opcao) {
            case '1':
                cadastrarAluno(alunos, &qtdAlunos);
                break;
            case '2':
                listarAlunos(alunos, qtdAlunos);
                break;
            case '0':
                printf(">>> Encerrando o programa. Ate logo!\n");
                break;
            default:
                printf(">>> Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != '0');

    return 0;
}

    
