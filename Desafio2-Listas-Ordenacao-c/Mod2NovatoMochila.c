#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

// Mochila Free Fire - Gerenciador de Itens
// Este programa permite gerenciar uma mochila de itens do jogo Free Fire.

// Definindo a estrutura do item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

#define MAX_ITENS 10

// Vetor global de itens e contador de itens atuais
Item mochila[MAX_ITENS];
int totalItens = 0;

// Função para inserir um novo item
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n⚠️  A mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novoItem;

    printf("\n=> Digite o nome do item: ");
    scanf("%s[^\n]", novoItem.nome);

    printf("=> Digite o tipo do item (Defesa, arma, municao, cura): ");
    scanf("%s[^\n]", novoItem.tipo);

    printf("=> Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);

    mochila[totalItens] = novoItem;
    totalItens++;

    printf("\n✅ Item adicionado com sucesso!\n");
}

// Função para remover um item pelo nome
void removerItem() {
    char nomeRemover[30];
    int encontrado = 0;

    printf("\n=> Digite o nome do item a ser removido: ");
    scanf("%s[^\n]", nomeRemover);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            // Sobrescreve o item removido com o último da lista
            mochila[i] = mochila[totalItens - 1];
            totalItens--;
            encontrado = 1;
            printf("\n🗑️  Item removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\n❌ Item não encontrado na mochila.\n");
    }
}

// Função para listar todos os itens
void listarItens() {
    if (totalItens == 0) {
        printf("\n📭 A mochila está vazia.\n");
        return;
    }

    printf("\n📦 Itens na mochila:\n");
    for (int i = 0; i < totalItens; i++) {
        printf("================================================\n");
        printf(" %d. Nome: %s | Tipo: %s | Quantidade: %d\n", i + 1,
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
        printf("================================================\n");
        printf("\n=> Total de itens: %d\n", totalItens);
}

// Função para buscar um item pelo nome
void buscarItem() {
    char nomeBusca[30];
    int encontrado = 0;

    printf("\n=> Digite o nome do item para busca: ");
    scanf(" %s[^\n]", nomeBusca);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n🔍 Item encontrado:\n");
            printf("================================================\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = 1;
            break;
        }
        printf("================================================\n");
        printf("\n=> Total de itens: %d\n", totalItens);

    }

    if (!encontrado) {
        printf("\n❌ Item não encontrado.\n");
    }
}

// Função principal com menu interativo
int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    int opcao;

    do {
        printf("\n========== MENU DA MOCHILA ==========\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("======================================\n");
        printf("\n=> Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("\n👋 Saindo do sistema de mochila...\n");
                break;
            default:
                printf("\n❗ Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
