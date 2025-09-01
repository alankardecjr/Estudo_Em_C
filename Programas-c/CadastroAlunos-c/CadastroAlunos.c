#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;            
} Pessoa;

int main() {
    //p ointer to a Person structure
    Pessoa*p = (Pessoa*)malloc(sizeof(Pessoa));

    printf("Enter name: ");
    scanf("%s", p->name);//Usamos a seta!

    printf("Enter age: ");
    scanf("%d", &p->age);//Usamos o operador de endereço!

    printf("%s tem %d anos.\n", p->name, p->age);

    free(p);    
    return 0;

    }

    
