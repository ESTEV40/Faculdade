// Alunos:                      Matrícula:
// Davi Roriz Oliveira          202210342
// Estêvão Souza Vieira         202210345

#include <stdio.h>

// Função multiply que realiza a multiplicação de base por expoente vezes usando exponenciação rápida
int multiply(int base, int expoente);

// Função potencia que utiliza a função auxiliar multiply
void potencia(int base, int expoente, int *result);

int main(void) {
    int base;
    int exponent;
    int result;

    while (scanf("%d %d", &base, &exponent) == 2) {
        potencia(base, exponent, &result);
        printf("%d\n", result);
        fflush(stdout);  // Garante que o buffer de saída seja gravado
    }

    return 0;
}

// Definindo a função multiply com __asm__ em Assembly Inline
__asm__ (
    ".globl multiply\n"       // Declara a função multiply como global
    "multiply:\n"             // Início da função multiply
    "movl $1, %ecx\n\t"       // Inicializa o registrador ECX com 1
    "jmp 1f\n\t"              // Salta para o rótulo 1
    "2:\n\t"                  // Rótulo 2
    "imull %edi, %edi\n\t"    // Multiplica EDI por EDI (base*base)
    "movl %esi, %eax\n\t"     // Move o valor de ESI para EAX (expoente)
    "shrl $31, %eax\n\t"      // Desloca EAX 31 bits para a direita (divide por 2^31)
    "addl %eax, %esi\n\t"     // Adiciona EAX a ESI
    "sarl %esi\n\t"           // Desloca ESI 1 bit para a direita (arithmetic shift)
    "1:\n\t"                  // Rótulo 1
    "testl %esi, %esi\n\t"    // Testa se ESI é zero
    "jle 3f\n\t"              // Se ESI <= 0, salta para o rótulo 3
    "movl %esi, %edx\n\t"     // Move o valor de ESI para EDX
    "shrl $31, %edx\n\t"      // Desloca EDX 31 bits para a direita
    "leal (%rsi,%rdx), %eax\n\t" // Carrega o endereço efetivo de (ESI + EDX) em EAX
    "andl $1, %eax\n\t"       // Faz um AND bit a bit entre EAX e 1
    "subl %edx, %eax\n\t"     // Subtrai EDX de EAX
    "cmpl $1, %eax\n\t"       // Compara EAX com 1
    "jne 2b\n\t"              // Se EAX != 1, volta para o rótulo 2
    "imull %edi, %ecx\n\t"    // Multiplica EDI por ECX (resultado intermediário)
    "jmp 2b\n\t"              // Volta para o rótulo 2
    "3:\n\t"                  // Rótulo 3
    "movl %ecx, %eax\n\t"     // Move o valor de ECX para EAX (resultado final)
    "ret\n\t"                 // Retorna
);

// Função potencia em Assembly inline usando __asm__()
__asm__ (
    ".globl potencia\n"       // Declara a função potencia como global
    "potencia:\n"             // Início da função potencia
    "pushq %rbx\n\t"          // Salva o valor de RBX na pilha
    "movq %rdx, %rbx\n\t"     // Move o ponteiro result para RBX
    "testl %esi, %esi\n\t"    // Testa se o expoente (ESI) é zero
    "jne 1f\n\t"              // Se ESI não for zero, salta para o rótulo 1
    "movl $1, (%rbx)\n\t"     // Se ESI for zero, armazena 1 no endereço apontado por RBX
    "jmp 2f\n\t"              // Salta para o rótulo 2
    "1:\n\t"                  // Rótulo 1
    "call multiply\n\t"       // Chama a função multiply
    "movl %eax, (%rbx)\n\t"   // Move o resultado de EAX para o endereço apontado por RBX
    "2:\n\t"                  // Rótulo 2
    "popq %rbx\n\t"           // Restaura o valor de RBX da pilha
    "ret\n\t"                 // Retorna
);


// // Função multiply que realiza a multiplicação de base por expoente vezes usando exponenciação rápida
// int multiply(int base, int expoente) {
//     int result = 1;  // Inicializa o resultado como 1

//     while (expoente > 0) { // Loop para calcular a potência de base elevado a expoente
//         if (expoente % 2 == 1) { // Se expoente for ímpar, multiplica result pelo valor atual de base
//             result *= base; // Multiplica result pela base atual
//         }
//         base *= base; // Eleva a base ao quadrado
//         expoente /= 2; // Divide o expoente por 2
//     }
//     return result; // Retorna o resultado final
// }

// // Função potencia que utiliza a função auxiliar multiply
// void potencia(int base, int expoente, int *result) {
//     if (expoente == 0) {  // Estrutura de desvio condicionado
//         *result = 1;  // Operação de atribuição via ponteiro
//     } else {  // Outra estrutura de desvio condicionado
//         *result = multiply(base, expoente);  // Chamada de função e atribuição via ponteiro
//     }
// }