//Estêvão Sousa Vieira - 202210345

// pai.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork(); // Cria um novo processo

    if (pid < 0) {
        // Se fork() retornar um valor negativo, houve um erro ao criar o processo filho
        fprintf(stderr, "Erro ao criar o processo filho\n");

        return 1;
    } else if (pid == 0) {
        // Processo filho executa execlp() para substituir a imagem do processo atual pelo programa "filho"
        execlp("./filho", "filho", NULL);
    } else {
        // Processo pai imprime seu nome e PID
        printf("Nome do aluno: Estêvão Sousa Vieira\nPID do pai: %d\n\n", getpid());
        // Processo pai espera o término do processo filho
        wait(NULL);
        printf("\n\nFim Processo Pai\n");
    }

    return 0;
}
