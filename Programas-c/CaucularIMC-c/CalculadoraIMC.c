#include <stdio.h>
#include <stdlib.h>

// Calculadora de IMC (Índice de Massa Corporal)
// Este programa calcula o IMC de uma pessoa com base no peso e altura fornecidos
// e classifica o resultado de acordo com as faixas de IMC estabelecidas pela OMS.

int main() {

    float peso, altura, imc;
    printf("\n***Calculadora de IMC***\n");
    printf("Digite seu peso: ");
    scanf("%f", &peso);
    printf("Digite sua altura: ");
    scanf("%f", &altura);
    imc = peso / (altura * altura);

    if (imc <= 18.5) {
        printf("Abaixo do Peso ");
    } else if (imc >= 18.6 && imc <= 24.9) {
        printf("Saudável ");
    } else if (imc >= 25.0 && imc <= 29.9) {
        printf("Peso em excesso ");
    } else if (imc >= 30.0 && imc <= 34.9) {
        printf("Obesidade Grau I ");
    } else if (imc > 35.0 && imc <= 39.9) {
        printf("Obesidade Grau II (severa)");
    } else {
        printf("Obesidade Grau III");
    }

    return 0;
}