//Estêvão Sousa Vieira - 202210345

// questao4.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main() {
    int a, b, c, d;
    printf("Digite dois valores para soma (a e b): ");
    scanf("%d %d", &a, &b);
    printf("Digite dois valores para multiplicação (c e d): ");
    scanf("%d %d", &c, &d);

    key_t key1 = ftok("shmfile1", 65); // Gera uma chave para a memória compartilhada 1
    key_t key2 = ftok("shmfile2", 75); // Gera uma chave para a memória compartilhada 2

    int shmid1 = shmget(key1, sizeof(int), 0666|IPC_CREAT); // Cria o segmento de memória compartilhada 1
    int shmid2 = shmget(key2, sizeof(int), 0666|IPC_CREAT); // Cria o segmento de memória compartilhada 2

    int *soma = (int*) shmat(shmid1, (void*)0, 0); // Anexa a memória compartilhada 1 ao espaço de endereçamento do processo
    int *mult = (int*) shmat(shmid2, (void*)0, 0); // Anexa a memória compartilhada 2 ao espaço de endereçamento do processo

    pid_t pid1 = fork();
    if (pid1 < 0) {
        // Se fork() retornar um valor negativo, houve um erro ao criar o processo filho 1
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        *soma = a + b; // Processo filho 1 calcula a soma e armazena na memória compartilhada
        printf("Filho 1 (PID: %d) - Soma: %d\n", getpid(), *soma);
        exit(EXIT_SUCCESS);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        // Se fork() retornar um valor negativo, houve um erro ao criar o processo filho 2
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        *mult = c * d; // Processo filho 2 calcula a multiplicação e armazena na memória compartilhada
        printf("Filho 2 (PID: %d) - Multiplicação: %d\n", getpid(), *mult);
        exit(EXIT_SUCCESS);
    }

    wait(NULL); // Espera pelo término do processo filho 1
    wait(NULL); // Espera pelo término do processo filho 2

    int resultado_final = *mult / *soma; // Processo pai calcula o resultado final usando os valores da memória compartilhada
    printf("Pai (PID: %d) - Resultado Final: %d\n", getpid(), resultado_final);

    shmdt(soma); // Desanexa a memória compartilhada 1
    shmdt(mult); // Desanexa a memória compartilhada 2

    shmctl(shmid1, IPC_RMID, NULL); // Marca a memória compartilhada 1 para destruição
    shmctl(shmid2, IPC_RMID, NULL); // Marca a memória compartilhada 2 para destruição

    return 0;
}
