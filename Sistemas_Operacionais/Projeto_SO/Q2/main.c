//Estêvão Sousa Vieira - 202210345

// questao2.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int a, b, c, d;
    printf("Digite dois valores para soma (a e b): ");
    scanf("%d %d", &a, &b);
    printf("Digite dois valores para multiplicação (c e d): ");
    scanf("%d %d", &c, &d);

    pid_t pid1 = fork();
    if (pid1 < 0) {
        // Se fork() retornar um valor negativo, houve um erro ao criar o processo filho 1
        fprintf(stderr, "Erro ao criar o processo filho 1\n");
        return 1;
    } else if (pid1 == 0) {
        // Primeiro processo filho realiza a soma de a e b
        int soma = a + b;
        printf("Filho 1 (PID: %d) - Soma: %d\n", getpid(), soma);
        exit(soma);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        // Se fork() retornar um valor negativo, houve um erro ao criar o processo filho 2
        fprintf(stderr, "Erro ao criar o processo filho 2\n");
        return 1;
    } else if (pid2 == 0) {
        // Segundo processo filho realiza a multiplicação de c e d
        int mult = c * d;
        printf("Filho 2 (PID: %d) - Multiplicação: %d\n", getpid(), mult);
        exit(mult);
    }

    // Processo pai espera pelos dois processos filhos
    int status1, status2;
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    // Pai recupera os resultados dos processos filhos
    int resultado_soma = WEXITSTATUS(status1);
    int resultado_mult = WEXITSTATUS(status2);
    int resultado_final = resultado_mult / resultado_soma;
    printf("Pai (PID: %d) - Resultado Final: %d\n", getpid(), resultado_final);

    return 0;
}