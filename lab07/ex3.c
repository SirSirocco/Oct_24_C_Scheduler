#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>

// Funções de operação no semáforo
void semaforoP(int semId) 
{
    struct sembuf semB;
    semB.sem_num = 0;
    semB.sem_op = -1;
    semB.sem_flg = SEM_UNDO;
    semop(semId, &semB, 1);
}

void semaforoV(int semId) 
{
    struct sembuf semB;
    semB.sem_num = 0;
    semB.sem_op = 1;
    semB.sem_flg = SEM_UNDO;
    semop(semId, &semB, 1);
}

// Função para criar memória compartilhada
int* criar_memoria_compartilhada(int* shmId) 
{
    *shmId = shmget(IPC_PRIVATE, sizeof(int), 0666 | IPC_CREAT);
    if (*shmId == -1) {
        perror("Falha ao criar memória compartilhada");
        exit(1);
    }
    return (int*) shmat(*shmId, NULL, 0);
}

// Função para remover memória compartilhada
void remover_memoria_compartilhada(int shmId) 
{
    shmctl(shmId, IPC_RMID, NULL);
}

int main() 
{
    int shmId, semId;
    int *shared_var;

    // Criando semáforo para controlar o acesso à variável
    semId = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    semctl(semId, 0, SETVAL, 1);  // Inicializando semáforo

    // Criando memória compartilhada para a variável
    shared_var = criar_memoria_compartilhada(&shmId);
    *shared_var = 0;  // Inicializando a variável compartilhada

    // Criando dois processos concorrentes
    pid_t pid = fork();

    if (pid == 0) 
    {  // Processo filho - soma 5
        while (1) 
        {
            semaforoP(semId);  // Trava o semáforo
            *shared_var += 5;
            printf("Processo filho (soma 5): valor da variável = %d\n", *shared_var);
            semaforoV(semId);  // Libera o semáforo
            sleep(2);  // Espera 2 segundos antes de repetir
        }
    } else {  // Processo pai - soma 1
        while (1) 
        {
            semaforoP(semId);  // Trava o semáforo
            *shared_var += 1;
            printf("Processo pai (soma 1): valor da variável = %d\n", *shared_var);
            semaforoV(semId);  // Libera o semáforo
            sleep(1);  // Espera 1 segundo antes de repetir
        }

        wait(NULL);  // Espera o processo filho terminar (o que nunca acontece nesse caso)
        remover_memoria_compartilhada(shmId);
    }

    return 0;
}
