#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicao da estrutura do no

typedef struct No {
    char valor[50];           // Valor armazenado no no (nome do ambiente)
    struct No* esquerda;      // Ponteiro para o filho a esquerda
    struct No* direita;       // Ponteiro para o filho a direita
    struct No* pai;           // Ponteiro para o ambiente anterior (pai)
} No;

// Funcao para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Funcao para criar um novo no (ambiente)
No* criarNo(const char* valor) {
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        fprintf(stderr, "*** Erro ao alocar memoria para o no *** %s\n", valor);
        exit(1);
    }
    strcpy(novo->valor, valor);
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->pai = NULL;
    return novo;
}

// Funcao para explorar ambientes da mansao
void explorarAmbientes(No* atual) {
    printf("\n>>> Inicio da exploracao interativa da mansao <<<\n");

    while (atual != NULL) {
        printf("\n>>> Voce esta no ambiente: %s\n", atual->valor);

        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\n>>> Este ambiente nao possui mais caminhos!\n");
            break;
        }

        printf(">>> Deseja ir para:\n");
        if (atual->esquerda) printf("     (e) - Esquerda: %s\n", atual->esquerda->valor);
        if (atual->direita) printf("     (d) - Direita: %s\n", atual->direita->valor);
        if (atual->pai)     printf("     (v) - Voltar para: %s\n", atual->pai->valor);
        printf("     (s) - Sair da exploracao\n");
        printf("\n>>> Escolha uma opcao: ");

        char escolha;
        scanf(" %c", &escolha);
        limparBuffer();

        if (escolha == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("\n>>> Nao ha ambiente a esquerda!\n");
            }
        } else if (escolha == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("\n>>> Nao ha ambiente a direita!\n");
            }
        } else if (escolha == 'v') {
            if (atual->pai != NULL) {
                atual = atual->pai;
            } else {
                printf("\n>>> Voce ja esta no inicio, nao ha como voltar mais!\n");
            }
        } else if (escolha == 's') {
            printf("\n>>> Exploracao encerrada pelo jogador <<<\n");
            break;
        } else {
            printf("*** Comando invalido. Use 'e', 'd', 'v' ou 's' ***\n");
        }
    }

    printf("\n>>> Fim do jogo <<<\n");
}

// Liberacao de memoria
void liberar(No* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esquerda);
        liberar(raiz->direita);
        free(raiz);
    }
}

// Funcao principal
int main() {
    // Criando os ambientes da mansao manualmente (estrutura fixa)
    No* hall = criarNo("Hall de Entrada");
    No* salaEstar = criarNo("Sala de Estar");
    No* biblioteca = criarNo("Biblioteca");
    No* suite1 = criarNo("Suite 1");
    No* suite2 = criarNo("Suite 2");
    No* escritorio = criarNo("Escritorio");
    No* copa = criarNo("Copa");
    No* cofre = criarNo("Cofre Secreto");

    // Montagem da estrutura
    hall->esquerda = salaEstar;
    hall->direita = biblioteca;
    salaEstar->esquerda = suite1;
    salaEstar->direita = suite2;
    biblioteca->direita = escritorio;
    biblioteca->esquerda = copa;
    escritorio->direita = cofre;

    // Definindo os pais (para permitir "voltar")
    salaEstar->pai = hall;
    biblioteca->pai = hall;
    suite1->pai = salaEstar;
    suite2->pai = salaEstar;
    copa->pai = biblioteca;
    escritorio->pai = biblioteca;
    cofre->pai = escritorio;

    // Inicio da execucao
    printf("\n===============================================================\n");
    printf("                   >>> Apresentacao do Mapa <<<                \n");
    printf("===============================================================\n");
    printf("\n            >>> Criacao da seguinte arvore binaria <<<        \n");
    printf("\n                        Hall de Entrada\n");
    printf("                               |\n");
    printf("                  -------------------------\n");
    printf("                  |                       |\n");
    printf("             Sala de Estar            Biblioteca\n");
    printf("                  |                        |\n");
    printf("            -------------             ------------\n");
    printf("            |           |             |          |\n");
    printf("         Suite 1     Suite 2        Copa    Escritorio\n");
    printf("                                                 |\n");
    printf("                                           Sala Secreta\n");
    printf("\n===============================================================\n");
    printf("        >>> Estrutura da mansao criada com sucesso <<<         \n");
    printf("===============================================================\n");

    // Exploracao interativa
    explorarAmbientes(hall);

    // Liberar memoria
    liberar(hall);

    return 0;
}

