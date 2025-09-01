#include <stdio.h>
#include <stdlib.h>

// Função de busca binária iterativa
int buscaBinariaIterativa(int vetor[], int tamanho, int valor) {
    int inicio = 0, fim = tamanho - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        if (vetor[meio] == valor)
            return meio;
        else if (vetor[meio] < valor)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1; // valor não encontrado
}

// Função de busca binária recursiva
int buscaBinariaRecursiva(int vetor[], int inicio, int fim, int valor) {
    if (inicio > fim)
        return -1;

    int meio = (inicio + fim) / 2;

    if (vetor[meio] == valor)
        return meio;
    else if (vetor[meio] < valor)
        return buscaBinariaRecursiva(vetor, meio + 1, fim, valor);
    else
        return buscaBinariaRecursiva(vetor, inicio, meio - 1, valor);
}

// Função de busca sequencial
int buscaSequencial(int vetor[], int tamanho, int valor) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == valor) {
            return i;
        }
    }
    return -1;
}

// Função principal para testar as funções de busca
int main() {
    int vetor[] = {1, 3, 5, 7, 9, 11, 13};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);
    int valor = 7;

    int resultado1 = buscaBinariaIterativa(vetor, tamanho, valor);
    int resultado2 = buscaBinariaRecursiva(vetor, 0, tamanho - 1, valor);
    int resultado3 = buscaSequencial(vetor, tamanho, valor);

    printf("Busca binária iterativa: índice = %d\n", resultado1);
    printf("Busca binária recursiva: índice = %d\n", resultado2);
    printf("Busca sequencial: índice = %d\n", resultado3);

    return 0;
}
