//Estêvão Sousa Vieira - 202210345

// questao3.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int a, b, c, d;
    int pipefd1[2], pipefd2[2];

    if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1) {
        // Se pipe() retornar -1, houve um erro ao criar os pipes
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    printf("Digite dois valores para soma (a e b): ");
    scanf("%d %d", &a, &b);
    printf("Digite dois valores para multiplicação (c e d): ");
    scanf("%d %d", &c, &d);

    pid_t pid1 = fork();
    if (pid1 < 0) {
        // Se fork() retornar um valor negativo, houve um erro ao criar o processo filho 1
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        close(pipefd1[0]); // Fecha o extremo de leitura do pipe 1
        int soma = a + b;
        write(pipefd1[1], &soma, sizeof(soma)); // Escreve o resultado da soma no pipe
        printf("Filho 1 (PID: %d) - Soma: %d\n", getpid(), soma);
        close(pipefd1[1]); // Fecha o extremo de escrita do pipe 1
        exit(EXIT_SUCCESS);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        // Se fork() retornar um valor negativo, houve um erro ao criar o processo filho 2
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        close(pipefd2[0]); // Fecha o extremo de leitura do pipe 2
        int mult = c * d;
        write(pipefd2[1], &mult, sizeof(mult)); // Escreve o resultado da multiplicação no pipe
        printf("Filho 2 (PID: %d) - Multiplicação: %d\n", getpid(), mult);
        close(pipefd2[1]); // Fecha o extremo de escrita do pipe 2
        exit(EXIT_SUCCESS);
    }

    close(pipefd1[1]); // Fecha o extremo de escrita do pipe 1 no pai
    close(pipefd2[1]); // Fecha o extremo de escrita do pipe 2 no pai
    int soma, mult;
    read(pipefd1[0], &soma, sizeof(soma)); // Lê o resultado da soma do pipe 1
    read(pipefd2[0], &mult, sizeof(mult)); // Lê o resultado da multiplicação do pipe 2
    close(pipefd1[0]); // Fecha o extremo de leitura do pipe 1
    close(pipefd2[0]); // Fecha o extremo de leitura do pipe 2

    int resultado_final = mult / soma;
    printf("Pai (PID: %d) - Resultado Final: %d\n", getpid(), resultado_final);

    wait(NULL); // Espera pelo término dos filhos
    wait(NULL);

    return 0;
}