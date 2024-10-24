#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>

// Estrutura da mensagem na memória compartilhada
struct shared_memory 
{
    char mensagem[100];
    int lida;  // Flag para indicar se a mensagem foi lida
};

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

// Função para conectar à memória compartilhada
struct shared_memory* conectar_memoria_compartilhada(int* shmId) 
{
    *shmId = shmget(1234, sizeof(struct shared_memory), 0666);
    if (*shmId == -1) {
        perror("Falha ao conectar à memória compartilhada");
        exit(1);
    }
    return (struct shared_memory*) shmat(*shmId, NULL, 0);
}

int main() 
{
    int shmId, semId;
    struct shared_memory *shm;

    // Conectando ao semáforo
    semId = semget(1234, 1, 0666);
    if (semId == -1) {
        perror("Falha ao conectar ao semáforo");
        exit(1);
    }

    // Conectando à memória compartilhada
    shm = conectar_memoria_compartilhada(&shmId);

    while (1) 
    {
        semaforoP(semId);  // Trava o semáforo para acessar a memória compartilhada

        if (shm->lida == 0) 
        {  // Se há uma mensagem nova, imprimi-la
            printf("Mensagem recebida: %s\n", shm->mensagem);
            shm->lida = 1;  // Marca a mensagem como lida
        }

        semaforoV(semId);  // Libera o semáforo
        sleep(1);  // Aguarda 1 segundo antes de verificar novamente
    }

    return 0;
}
