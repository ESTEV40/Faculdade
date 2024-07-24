#include <stdio.h>


long long int Potencia(long long int i){
    long long int mont = 1;

    for(long long int cont = 0; cont <= i; cont++)
        mont = 2 * mont;

    return mont; 
}

// Funcao para converter um numero inteiro para uma string binaria
void intToBinary(long long int n, long long int w, char *binary) {
    for (long long int i = w - 1 ; i >= 0 ; i--) {
        binary[i] = (n & 1) ? '1' : '0';
        n >>= 1;
    }
    binary[w] = '\0'; // Adiciona o terminador de string
}

// Funcao para calcular o valor signed T em complemento de dois
long long int complemento2(long long int U, long long int w) {
    long long int aux = Potencia(w - 1);
    if (U >= aux) {
        return U - Potencia(w);
    } else {
        return U;
    }
}

int main(void) {
    long long int w;

    // Solicita o valor de W ao usuario
    printf("Insira o valor de w: ");
    scanf("%d", &w);

    // Quantidade de cadeias binarias de tamanho W
    long long int qtd = Potencia(w);

    // Imprime as colunas da tabela
    printf("Binary\tU\tT\n");

    // Loop para calcular e imprimir cada linha da tabela
    for (long long int i = 0 ; i < qtd ; i++) {
        char binary[w + 1];
        intToBinary(i, w, binary);
        long long int U = i;
        long long int T = complemento2(U, w);

        printf("%s\t%d\t%d\n", binary, U, T);
    }
    
    return 0;
}