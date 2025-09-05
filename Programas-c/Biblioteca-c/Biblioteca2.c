// Biblioteca.c
// Biblioteca.c - Sistema de Gerenciamento de Biblioteca
// Este programa permite o cadastro, empréstimo e devolução de livros em uma biblioteca.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>


// Definições
//Constantes Globais

#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100
#define TAM_STRING 100

//Definição das Estruturas
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel; // 0 = disponível, 1 = alugado
};

struct Emprestimo { 
    int indiceLivro; // índice do livro na lista de livros
    char nomeUsuario[TAM_STRING];
    char dataEmprestimo[TAM_STRING];
    char dataDevolucao[TAM_STRING];
};

// Protótipos das Funções
//Declarar as Funções, aqui permite que a 'main' as chame antes de suas definições
void limparBufferEntrada();
void exibirMenu();
void cadastrarLivro(struct Livro *biblioteca, int *totalLivros);
void listarLivros(const struct Livro *biblioteca, int *totalLivros);
void registrarEmprestimo(struct Livro *biblioteca, int *totalLivros, struct Emprestimo *emprestimos, int *totalEmprestimos);
void registrarDevolucao(struct Livro *biblioteca, struct Emprestimo *emprestimos, int *totalEmprestimos);
void listarEmprestimos(struct Livro *biblioteca, struct Emprestimo *emprestimos, int totalEmprestimos);
void liberarMemoria(struct Livro *biblioteca, struct Emprestimo *emprestimos);

//Função Principal(main)
//A função main é o ponto de entrada do programa, onde a execução começa

int main() {
    setlocale(LC_ALL, "pt_BR"); // Configura a localidade para UTF-8
    //Alocação Dinâmica de Memória para os arrays de livros e empréstimos

    struct Livro *biblioteca = (struct Livro *) calloc(MAX_LIVROS, sizeof(struct Livro));
    struct Emprestimo *emprestimos = (struct Emprestimo *) malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));
    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;  

    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                cadastrarLivro(biblioteca, &totalLivros);
                break;
            case 2:
                listarLivros(biblioteca, &totalLivros);
                break;
            case 3:
                registrarEmprestimo(biblioteca, &totalLivros, emprestimos, &totalEmprestimos);
                break;
            case 4:
                registrarDevolucao(biblioteca, emprestimos, &totalEmprestimos);
                break;
            case 5:
                listarEmprestimos(biblioteca, emprestimos, totalEmprestimos);
                break;
                case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                getchar();
                break;
        }

    } while (opcao != 0);

    //Chamando a função para liberar a memória alocada
    liberarMemoria(biblioteca, emprestimos);
    return 0;
}

// Implementação das Funções
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirMenu() {
    printf("\n================================================\n");
    printf("|==  Sistema de Gerenciamento de Biblioteca  ==|");
    printf("\n================================================\n");
    printf("*** 1. Cadastrar Livro                       ***\n");
    printf("*** 2. Listar Livros                         ***\n");
    printf("*** 3. Registrar Emprestimo                 ***\n");
    printf("*** 4. Registrar Devolução                 ***\n");
    printf("*** 5. Listar Emprestimos                   ***\n");
    printf("*** 0. Sair                                  ***\n");
    printf("================================================\n\n");
    printf("\n->Escolha uma opção:\n");
}

void cadastrarLivro(struct Livro *biblioteca, int *totalLivros) {
    printf("\n----------------------------------\n");
    printf("|----   Cadastro de Livro:   ----|");
    printf("\n----------------------------------\n\n");

    // Verifica se ainda há espaço para cadastrar mais livros
    // Se o totalLivros for menor que MAX_LIVROS, permite o cadastro    

    if (*totalLivros < MAX_LIVROS) {
        int indice = *totalLivros; //Usa o valor apontado pelo ponteiro para o indice do livro

        printf("> Digite o nome do livro: ");
        fgets(biblioteca[indice].nome, TAM_STRING, stdin);
        printf("> Digite o nome do autor: ");
        fgets(biblioteca[indice].autor, TAM_STRING, stdin);
        printf("> Digite o nome da editora: ");
        fgets(biblioteca[indice].editora, TAM_STRING, stdin);   

        biblioteca[indice].nome[strcspn(biblioteca[indice].nome, "\n")] = 0;
        biblioteca[indice].autor[strcspn(biblioteca[indice].autor, "\n")] = 0;
        biblioteca[indice].editora[strcspn(biblioteca[indice].editora, "\n")] = 0;

        printf("> Digite a edicao do Livro: ");
        scanf("%d", &biblioteca[indice].edicao);
        printf("----------------------------------\n");
        limparBufferEntrada();

        biblioteca[indice].disponivel = 0; // Marca o livro como disponível

        (*totalLivros)++; // Incrementa o valor da variável totalLivros
        printf("\n*** Livro cadastrado com sucesso! ***\n");
    } else {
        printf("\n***** Biblioteca cheia! *****\n");
    }
    printf("\n\n----- Presione Enter para continuar... -----\n");
    getchar();
}

void listarLivros(const struct Livro *biblioteca, int *totalLivros) {
    printf("\n==================================\n");
    printf("|= Lista de Livros cadastrados: =|");
    printf("\n==================================\n");

    // Verifica se há livros cadastrados
    // Se o totalLivros for igual a 0, informa que não há livros cadastrados

    if (*totalLivros == 0) {
        printf("\n***** Nenhum livro cadastrado! *****\n");
    } else {
        for (int i = 0; i < *totalLivros; i++) {
            printf("\n--------------------------------\n");
            printf("|****       Livro       %d: ****|", i + 1);
            printf("\n--------------------------------\n");
            printf("> Nome: %s\n", biblioteca[i].nome);
            printf("> Autor: %s\n", biblioteca[i].autor);
            printf("> Editora: %s\n", biblioteca[i].editora);
            printf("> Edicao: %d\n", biblioteca[i].edicao);
            printf("> Disponivel: %s\n", biblioteca[i].disponivel == 0 ? "Sim" : "Não");
            printf("--------------------------------\n");            
        }
            printf("\n*********************************\n");
    }
    printf("\n----- Pressione Enter para continuar... -----\n");
    getchar();
}

void registrarEmprestimo(struct Livro *biblioteca, int *totalLivros, struct Emprestimo *emprestimos, int *totalEmprestimos) {
    printf("\n-----------------------------------\n");
    printf("|----  Realizar emprestimo:  ----|");
    printf("\n-----------------------------------\n");

    if (*totalEmprestimos >= MAX_EMPRESTIMOS) {
        printf("\n***** Limite de emprestimos atingido! *****\n");
    } else {
        printf("\n***** Livros disponiveis: *****\n\n");
        int livrosDisponiveis = 0;
        for (int i = 0; i < *totalLivros; i++) {
            if (biblioteca[i].disponivel == 0) {
                printf("> %d - %s\n", i + 1, biblioteca[i].nome);
                livrosDisponiveis++;
            }
            printf("--------------------------------\n");
        }
    
        if (livrosDisponiveis == 0) {
            printf("\n*** Nenhum livro disponivel para emprestimo! ***\n");
        } else {
            printf("\n> Digite o numero do livro que deseja emprestar: ");
            int indiceLivro;
            scanf("%d", &indiceLivro);
            limparBufferEntrada();

            int indice = indiceLivro - 1; // Ajusta o índice para começar de 0

            if (indice >= 0 && indice < *totalLivros && biblioteca[indice].disponivel == 0) {
                printf("\n> Digite o nome do usuario: ");
                fgets(emprestimos[*totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                emprestimos[*totalEmprestimos].nomeUsuario[strcspn(emprestimos[*totalEmprestimos].nomeUsuario, "\n")] = 0;

                printf("> Digite a data de emprestimo (DD/MM/AAAA): ");
                fgets(emprestimos[*totalEmprestimos].dataEmprestimo, TAM_STRING, stdin);
                emprestimos[*totalEmprestimos].dataEmprestimo[strcspn(emprestimos[*totalEmprestimos].dataEmprestimo, "\n")] = 0;
                // Registra o empréstimo
                emprestimos[*totalEmprestimos].dataDevolucao[0] = '\0'; // Inicializa a data de devolução como vazia
                

                emprestimos[*totalEmprestimos].indiceLivro = indice;
                biblioteca[indice].disponivel = 1; // Marca o livro como não disponível

                (*totalEmprestimos)++; // Incrementa o total de empréstimos
                printf("\n***** Emprestimo registrado com sucesso! *****\n");
            } else {
                printf("\n***** Livro invalido ou nao disponivel! *****\n");
            }   
        }
    }
    printf("\n----- Pressione Enter para continuar... -----\n");
    getchar();
}

void registrarDevolucao(struct Livro *biblioteca, struct Emprestimo *emprestimos, int *totalEmprestimos) {
    printf("\n----------------------------------------\n");
    printf("|----    Registrar devolucao:    ----|");
    printf("\n----------------------------------------\n\n");
    
    if (*totalEmprestimos == 0) {
        printf("\n***** Nenhum emprestimo registrado! *****\n");
    }   else {  
        printf("*****     Emprestimos ativos:     *****\n\n");
        for (int i = 0; i < *totalEmprestimos; i++) {
            printf("> %d - Livro: %s, Usuario: %s\n", i + 1, biblioteca[emprestimos[i].indiceLivro].nome, emprestimos[i].nomeUsuario);
        }  
        printf("\n----------------------------------------\n"); 
        printf("\n> Digite o número do livro a ser devolvido: ");
        int indiceEmprestimo;
        scanf("%d", &indiceEmprestimo);
        limparBufferEntrada();  
        int indice = indiceEmprestimo - 1; // Ajusta o índice para começar de 0

        if (indice >= 0 && indice < *totalEmprestimos) {    
            biblioteca[emprestimos[indice].indiceLivro].disponivel = 1; // Marca o livro como disponível
            printf("\n> Digite a data de devolucao (DD/MM/AAAA): ");
            fgets(emprestimos[indice].dataDevolucao, TAM_STRING, stdin);
            emprestimos[indice].dataDevolucao[strcspn(emprestimos[indice].dataDevolucao, "\n")] = 0;
            printf("\n*****    Devolucao registrada com sucesso!    *****\n\n");
            // Remove o empréstimo do array
            for (int j = indice; j < *totalEmprestimos - 1; j++) {  
                emprestimos[j] = emprestimos[j + 1];
            }
            (*totalEmprestimos)--; // Decrementa o total de empréstimos
        }
        else {
            printf("\n***** Emprestimo invalido! *****\n");
        }
    }
    printf("\n----- Pressione Enter para continuar... -----\n");
    getchar();
}

void listarEmprestimos(struct Livro *biblioteca, struct Emprestimo *emprestimos, int totalEmprestimos) {
    printf("\n------------------------------------\n");
    printf("|----  Lista de Emprestimos:  ----|");
    printf("\n------------------------------------\n\n");

    if (totalEmprestimos == 0) {
        printf("\n***** Nenhum emprestimo registrado! *****\n\n");    
    } else {
        for (int i = 0; i < totalEmprestimos; i++) {
            printf("\n--------------------------------\n");
            printf("\n***** Emprestimo %d: *****\n", i + 1);
            printf("> Livro: %s\n", biblioteca[emprestimos[i].indiceLivro].nome);
            printf("> Autor: %s\n", biblioteca[emprestimos[i].indiceLivro].autor);
            printf("> Usuario: %s\n", emprestimos[i].nomeUsuario);
            printf("> Data de Emprestimo: %s\n", emprestimos[i].dataEmprestimo);    
            printf("> Data de Devolucao: %s\n", emprestimos[i].dataDevolucao);

        }
        printf("\n--------------------------------\n");
    }
    printf("\n----- Pressione Enter para continuar... -----\n");
    getchar();
}
void liberarMemoria(struct Livro *biblioteca, struct Emprestimo *emprestimos) {
    free(biblioteca);
    free(emprestimos);
    printf("\n***** Memoria liberada com sucesso! *****\n");
}
// Fim do código Biblioteca.c
// Biblioteca.c - Sistema de Gerenciamento de Biblioteca
// Este programa permite o cadastro, empréstimo e devolução de livros em uma biblioteca.