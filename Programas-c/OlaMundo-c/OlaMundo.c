#include <stdio.h>

// Função que imprime uma saudação
void saudacao(void) {
    printf("Ola, mundo!\n");
}

int main(void) {
    void (*ptr)(void) = saudacao; // ponteiro para função
    ptr(); // chamada indireta
    
    return 0;
}