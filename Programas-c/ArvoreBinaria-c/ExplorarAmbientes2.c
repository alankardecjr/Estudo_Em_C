#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR 100

// ---------------------------------------------------------------
// ESTRUTURAS DE DADOS
// ---------------------------------------------------------------

// Estrutura de um nó da árvore de cômodos da mansão
typedef struct Sala {
    char nome[MAX_STR];          // Nome do cômodo (ex: "Sala de Estar")
    char pista[MAX_STR];         // Pista opcional encontrada no cômodo
    struct Sala* esquerda;       // Caminho à esquerda
    struct Sala* direita;        // Caminho à direita
    struct Sala* pai;            // Caminho de volta (pai)
} Sala;

// Estrutura de um nó da árvore BST de pistas
typedef struct PistaNode {
    char pista[MAX_STR];              // Conteúdo da pista
    struct PistaNode* esquerda;       // Subárvore à esquerda (menores)
    struct PistaNode* direita;        // Subárvore à direita (maiores)
} PistaNode;

// FUNÇÕES AUXILIARES

// Limpa o buffer do teclado após leitura de caractere
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para criar dinamicamente uma sala com ou sem pista
Sala* criarSala(const char* nome, const char* pista) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    if (!nova) {
        fprintf(stderr, ">>> ERRO: Falha ao alocar memoria para sala %s\n", nome);
        exit(1);
    }

    strcpy(nova->nome, nome);
    if (pista != NULL)
        strcpy(nova->pista, pista);
    else
        nova->pista[0] = '\0';

    nova->esquerda = nova->direita = nova->pai = NULL;
    return nova;
}

// Função para criar um nó da árvore de pistas (BST)
PistaNode* criarPistaNode(const char* pista) {
    PistaNode* novo = (PistaNode*) malloc(sizeof(PistaNode));
    if (!novo) {
        fprintf(stderr, ">>> ERRO: Falha ao alocar memoria para pista\n");
        exit(1);
    }

    strcpy(novo->pista, pista);
    novo->esquerda = novo->direita = NULL;
    return novo;
}

// Função para inserir uma nova pista na BST (ordem alfabética)
PistaNode* inserirPista(PistaNode* raiz, const char* pista) {
    if (raiz == NULL)
        return criarPistaNode(pista);

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);

    return raiz;
}

// Função para exibir as pistas armazenadas em ordem alfabética
void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

// Libera memória da árvore de pistas
void liberarPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}

// Libera memória da árvore de cômodos
void liberarSalas(Sala* raiz) {
    if (raiz != NULL) {
        liberarSalas(raiz->esquerda);
        liberarSalas(raiz->direita);
        free(raiz);
    }
}

// FUNÇÃO DE EXPLORAÇÃO DA MANSÃO

// Controla a navegação entre salas e coleta automática de pistas
void explorarSalasComPistas(Sala* atual, PistaNode** pistasColetadas) {
    printf("\n>>> Inicio da exploracao <<<\n");

    while (atual != NULL) {
        printf("\n>>> Voce esta: %s\n", atual->nome);

        // Coleta automática da pista, se houver
        if (strlen(atual->pista) > 0) {
            printf(">>> Pista encontrada: \"%s\"\n", atual->pista);
            *pistasColetadas = inserirPista(*pistasColetadas, atual->pista);
        } else {
            printf(">>> Nenhuma pista neste comodo.\n");
        }

        // Apresenta as opções disponíveis ao jogador
        printf("\n>>> Escolha uma direcao:\n");
        if (atual->esquerda) printf("   (e) - Esquerda: %s\n", atual->esquerda->nome);
        if (atual->direita)  printf("   (d) - Direita:  %s\n", atual->direita->nome);
        if (atual->pai)      printf("   (v) - Voltar para: %s\n", atual->pai->nome);
        printf("   (s) - Sair da exploracao\n");

        // Leitura da escolha do jogador
        printf(">>> Opcao: ");
        char opcao;
        scanf(" %c", &opcao);
        limparBuffer();

        // Tratamento da escolha
        if (opcao == 'e' && atual->esquerda) {
            atual = atual->esquerda;
        } else if (opcao == 'd' && atual->direita) {
            atual = atual->direita;
        } else if (opcao == 'v' && atual->pai) {
            atual = atual->pai;
        } else if (opcao == 's') {
            printf("\n>>> Exploracao encerrada pelo jogador <<<\n");
            break;
        } else {
            printf(">>> Comando invalido ou caminho inexistente.\n");
        }
    }

}

// FUNÇÃO PRINCIPAL
int main() {
    // Criando os ambientes da mansão manualmente (estrutura fixa)
    Sala* hall        = criarSala("Hall de Entrada", "Pegadas de lama fresca");
    Sala* salaEstar   = criarSala("Sala de Estar", "Bilhete amassado");
    Sala* biblioteca  = criarSala("Biblioteca", "Agenda com pagina faltando");
    Sala* suite1      = criarSala("Suite 1", "Camisa com marca de batom");
    Sala* sacada      = criarSala("Sacada", "");
    Sala* suite2      = criarSala("Suite 2", "");
    Sala* escritorio  = criarSala("Escritorio", "Lencos com manchas de sangue");
    Sala* copa        = criarSala("Copa", "Xicaras quebradas");
    Sala* cofre       = criarSala("Banker", "Fotos denunciando chantagem");

    // Montagem da estrutura da mansão
    hall->esquerda = salaEstar;
    hall->direita = biblioteca;
    salaEstar->esquerda = suite1;
    suite1->esquerda = sacada;
    salaEstar->direita = suite2;
    biblioteca->esquerda = copa;
    biblioteca->direita = escritorio;
    escritorio->direita = cofre;

    // Definindo os pais (para permitir "voltar")
    salaEstar->pai = hall;
    biblioteca->pai = hall;
    suite1->pai = salaEstar;
    sacada->pai = suite1;
    suite2->pai = salaEstar;
    copa->pai = biblioteca;
    escritorio->pai = biblioteca;
    cofre->pai = escritorio;

    // Apresentação do Mapa
    printf("\n===============================================================\n");
    printf("                      >>> Mapa da Mansao <<<                   \n");
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
    printf("            |                                     |\n");
    printf("          Sacada                                Banker\n");
    printf("\n===============================================================\n");
    printf("        >>> Estrutura da mansao criada com sucesso <<<         \n");
    printf("===============================================================\n");

    // Variável para armazenar as pistas coletadas
    PistaNode* pistas = NULL;

    // Início da exploração da mansão
    explorarSalasComPistas(hall, &pistas);

    // Exibição final das pistas coletadas
    printf("\n===============================================================\n");
    printf("               >>> PISTAS COLETADAS EM ORDEM <<<               \n");
    printf("===============================================================\n");

    if (pistas != NULL)
        exibirPistas(pistas);
    else
        printf(">>> Nenhuma pista foi coletada.\n");

    // Liberação de memória
    liberarSalas(hall);
    liberarPistas(pistas);

    printf("\n===============================================================\n");
    printf("       >>> Fim da investigacao. Boa sorte, detetive! <<<       \n");
    printf("===============================================================\n");

    printf("\n");
    return 0;
}
