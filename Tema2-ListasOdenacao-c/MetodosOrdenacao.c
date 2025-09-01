#include<stdio.h>
#include<stdlib.h>

// Função para trocar dois elementos
void trocar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para ordenar um array usando o algoritmo Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                trocar(&arr[j], &arr[j+1]);
            }
        }
    }
}

// Função para ordenar um array usando o algoritmo Insertion Sort
void insertionSort(int vetor[], int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        int chave = vetor[i];
        int j = i - 1;

        // Move os elementos maiores que a chave uma posição à frente
        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j--;
        }

        vetor[j + 1] = chave;
    }
} 

// Função para ordenar um array usando o algoritmo Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        trocar(&arr[min_idx], &arr[i]);
    }
}   

// Função para imprimir um array
void imprimirArray(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Função principal para testar os algoritmos de ordenação
int main() {    
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int n1 = sizeof(arr1)/sizeof(arr1[0]);
    bubbleSort(arr1, n1);
    printf("Array ordenado usando Bubble Sort: \n");
    imprimirArray(arr1, n1);

    int arr2[] = {12, 11, 13, 5, 6};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
    insertionSort(arr2, n2);
    printf("Array ordenado usando Insertion Sort: \n");
    imprimirArray(arr2, n2);

    int arr3[] = {64, 25, 12, 22, 11};
    int n3 = sizeof(arr3)/sizeof(arr3[0]);
    selectionSort(arr3, n3);
    printf("Array ordenado usando Selection Sort: \n");
    imprimirArray(arr3, n3);

    return 0;
}




