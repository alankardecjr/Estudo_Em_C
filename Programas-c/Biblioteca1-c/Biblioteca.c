#include <stdio.h>
#include <string.h>

#define MAX_LIVROS 5
#define TAM 100

typedef struct {
    char titulo[TAM];
    char autor[TAM];
    int edicao;
    int alugado; // 0 = disponível, 1 = alugado
} Livro;

void cadastrarLivros(Livro livros[]) {
    for (int i = 0; i < MAX_LIVROS; i++) {
        printf("Cadastro do livro %d:\n", i + 1);
        printf("Título: ");
        fgets(livros[i].titulo, TAM, stdin);
        livros[i].titulo[strcspn(livros[i].titulo, "\n")] = 0; // remove \n

        printf("Autor: ");
        fgets(livros[i].autor, TAM, stdin);
        livros[i].autor[strcspn(livros[i].autor, "\n")] = 0;

        printf("Edição: ");
        scanf("%d", &livros[i].edicao);
        getchar(); // limpa buffer

        printf("Está alugado? (1 = Sim, 0 = Não): ");
        scanf("%d", &livros[i].alugado);
        getchar();
        printf("\n");
    }
}

void pesquisarLivro(Livro livros[]) {
    char busca[TAM];
    printf("Digite o título do livro para pesquisar: ");
    fgets(busca, TAM, stdin);
    busca[strcspn(busca, "\n")] = 0;

    int encontrado = 0;
    for (int i = 0; i < MAX_LIVROS; i++) {
        if (strcmp(livros[i].titulo, busca) == 0) {
            printf("Livro encontrado:\n");
            printf("Título: %s\nAutor: %s\nEdição: %d\n", livros[i].titulo, livros[i].autor, livros[i].edicao);
            printf("Disponibilidade: %s\n", livros[i].alugado ? "Alugado" : "Disponível");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Livro não encontrado.\n");
    }
}

int main() {
    Livro livros[MAX_LIVROS];
    cadastrarLivros(livros);

    char opcao;
    do {
        printf("\nPesquisar livro? (s/n): ");
        scanf(" %c", &opcao);
        getchar();
        if (opcao == 's' || opcao == 'S') {
            pesquisarLivro(livros);
        }
    } while (opcao == 's' || opcao == 'S');

    return 0;
}