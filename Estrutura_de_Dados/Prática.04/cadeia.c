#include <stdio.h>
#include <stdlib.h>
// Pilha de caracteres
// Só percebi agora que isso aqui não é muito bem pilha...
struct Stack {
    char *letras;
    int tamanho;
};
typedef struct Stack Pilha;

void empilhar(Pilha *);// empilha caracteres
int verifica(Pilha);// verifica se a pilha forma um palíndromo

int main() {
    Pilha cadeia;
  
    while (scanf("%d", &cadeia.tamanho) == 1) {//Termina com o fim das entradas
        empilhar(&cadeia);
        if (verifica(cadeia) == 0)
            printf("SIM\n");
        else
            printf("NAO\n");
        free(cadeia.letras);
    }
}

void empilhar(Pilha *A) {
    A->letras = malloc(sizeof(char) * (A->tamanho + 1));
    scanf("%s", A->letras);
}

int verifica(Pilha A) {
    int aux1=0, aux2 = A.tamanho-1;
    for(aux1 = 0; aux2 >= aux1 ; aux1++, aux2--){ //verifica pelo inicio e fim da pilha
        if(A.letras[aux1] != A.letras[aux2]){
            return 1;
        }
    }
    return 0;
}
