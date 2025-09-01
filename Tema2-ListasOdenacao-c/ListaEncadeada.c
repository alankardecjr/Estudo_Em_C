#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<locale.h>

#define TAM_NOME 100
#define TAM_TEL 15
#define TAM_CPF 11

typedef struct Contato {
    char nome[TAM_NOME];
    char telefone[TAM_TEL];
    char cpf[TAM_CPF];
    struct Contato* proximo;
} Contato;

// Função para criar um novo contato
Contato* criarContato(const char* nome, const int* telefone, const int* cpf) {
    Contato* novo = (Contato*)malloc(sizeof(Contato));
    if (novo) {
        strncpy(novo->nome, nome, TAM_NOME);
        strncpy(novo->telefone, telefone, TAM_TEL);
        strncpy(novo->cpf, cpf, TAM_CPF);
        novo->proximo = NULL;
    }
    return novo;
}

// Inserir contato no início da lista
void inserirContato(Contato** inicio, const char* nome, const char* telefone, const char* cpf) {
    Contato* novo = criarContato(nome, telefone, cpf);
    if (novo) {
        novo->proximo = *inicio;
        *inicio = novo;
        printf("Contato inserido com sucesso!\n");
    } else {
        printf("Erro ao alocar memória!\n");
    }
}

// Listar todos os contatos
void listarContatos(Contato* inicio) {
    if (!inicio) {
        printf("Nenhum contato cadastrado.\n");
        return;
    }
    int i = 1;
    while (inicio) {
        printf("Contato %d:\n", i++);
        printf("Nome: %s\n", inicio->nome);
        printf("Telefone: %s\n", inicio->telefone);
        printf("CPF: %s\n\n", inicio->cpf);
        inicio = inicio->proximo;
    }
}

// Buscar contato por CPF
Contato* buscarContato(Contato* inicio, const char* cpf) {
    while (inicio) {
        if (strcmp(inicio->cpf, cpf) == 0) {
            return inicio;
        }
        inicio = inicio->proximo;
    }
    return NULL;
}

// Editar contato
void editarContato(Contato* inicio, const char* cpf) {
    Contato* contato = buscarContato(inicio, cpf);
    if (contato) {
        printf("Novo nome: ");
        fgets(contato->nome, TAM_NOME, stdin);
        contato->nome[strcspn(contato->nome, "\n")] = 0;
        printf("Novo telefone: ");
        fgets(contato->telefone, TAM_TEL, stdin);
        contato->telefone[strcspn(contato->telefone, "\n")] = 0;
        printf("Contato atualizado!\n");
    } else {
        printf("Contato não encontrado.\n");
    }
}

// Excluir contato
void excluirContato(Contato** inicio, const char* cpf) {
    Contato* atual = *inicio;
    Contato* anterior = NULL;
    while (atual) {
        if (strcmp(atual->cpf, cpf) == 0) {
            if (anterior) {
                anterior->proximo = atual->proximo;
            } else {
                *inicio = atual->proximo;
            }
            free(atual);
            printf("Contato excluído!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Contato não encontrado.\n");
}

// Liberar memória da lista
void liberarLista(Contato* inicio) {
    Contato* temp;
    while (inicio) {
        temp = inicio;
        inicio = inicio->proximo;
        free(temp);
    }
}

int main() {
    setlocale(LC_ALL, "pt_BR"); // Configura a localidade para UTF-8
    Contato* lista = NULL;
    int opcao;
    char nome[TAM_NOME], telefone[TAM_TEL], cpf[TAM_CPF];

    do {
        printf("\n|======== MENU ========|\n");
        printf("| >1. Inserir contato  |\n");
        printf("| >2. Listar contatos  |\n");
        printf("| >3. Editar contato   |\n");
        printf("| >4. Excluir contato  |\n");
        printf("| >0. Sair             |\n");
        printf("|======================|\n");
        printf("\n *Escolha uma opção:*\n");
        printf("\n=>");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        switch (opcao) {
            case 1:
                printf("Nome: ");
                fgets(nome, TAM_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;
                printf("Telefone: ");
                fgets(telefone, TAM_TEL, stdin);
                telefone[strcspn(telefone, "\n")] = 0;
                printf("CPF: ");
                fgets(cpf, TAM_CPF, stdin);
                cpf[strcspn(cpf, "\n")] = 0;
                inserirContato(&lista, nome, telefone, cpf);
                break;
            case 2:
                listarContatos(lista);
                break;
            case 3:
                printf("Digite o CPF do contato a editar: ");
                fgets(cpf, TAM_CPF, stdin);
                cpf[strcspn(cpf, "\n")] = 0;
                editarContato(lista, cpf);
                break;
            case 4:
                printf("Digite o CPF do contato a excluir: ");
                fgets(cpf, TAM_CPF, stdin);
                cpf[strcspn(cpf, "\n")] = 0;
                excluirContato(&lista, cpf);
                break;
            case 0:
                liberarLista(lista);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

}