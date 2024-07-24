// Davi Roriz Oliveira - 202210342
// Estevao Souza Vieira - 202210345

#include <stdio.h>
#include <limits.h>

// Funcao para converter um numero inteiro para uma string binaria
void intToBinary(unsigned long long int n, int w, char *binary) {
    for (int i = w - 1 ; i >= 0 ; i--) {
        binary[i] = (n & 1ULL) ? '1' : '0';
        n >>= 1;
    }
    binary[w] = '\0'; // Adiciona o terminador de string
}

// Funcao para calcular o valor signed T em complemento de 2
long long int complemento2(unsigned long long int U, unsigned long long int aux, unsigned long long int qtd) {
    if (U >= aux) {
        return U - qtd;
    } else {
        return U;
    }
}

int main(void) {
    int w;

    // Solicita o valor de W ao usuario
    printf("Insira o valor de w: ");
    scanf("%d", &w);

    // Verifica se W eh um valor valido
    if (w <= 0 || w > sizeof(unsigned long long int) * CHAR_BIT) {
        printf("Valor de w fora do intervalo suportado\n");
        return 1;
    } else {
    // Quantidade de cadeias binarias de tamanho W
    unsigned long long int qtd = 1ULL << w;
    unsigned long long int aux = 1ULL << (w - 1);

    // Verifica se há pelo menos 10 cadeias para imprimir
    if (qtd <= 10) {
        printf("Binary\t\tU\tT\n");
        for (unsigned long long int i = 0 ; i < qtd ; i++) {
            char binary[w + 1];
            intToBinary(i, w, binary);
            
            unsigned long long int U = i;
            long long int T = complemento2(U, aux, qtd);
            
            printf("%s\t%llu\t%lld\n", binary, U, T);
        }
    } else {
        // Calcula o ponto de partida para as cadeias centrais
        unsigned long long int start = (qtd - 10) / 2;
        
        // Imprime as colunas da tabela
        printf("Binary\t\tU\tT\n");

        // Loop para calcular e imprimir as 10 cadeias centrais
        for (unsigned long long int i = start ; i < start + 10 ; i++) {
            char binary[w + 1];
            intToBinary(i, w, binary);
            
            unsigned long long int U = i;
            long long int T = complemento2(U, aux, qtd);
            
            printf("%s\t%llu\t%lld\n", binary, U, T);
        }
    }
}
    return 0;
}