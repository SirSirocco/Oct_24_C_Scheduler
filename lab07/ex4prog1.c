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

// Função para criar memória compartilhada
struct shared_memory* criar_memoria_compartilhada(int* shmId) 
{
    *shmId = shmget(1234, sizeof(struct shared_memory), 0666 | IPC_CREAT);
    if (*shmId == -1) {
        perror("Falha ao criar memória compartilhada");
        exit(1);
    }
    return (struct shared_memory*) shmat(*shmId, NULL, 0);
}

int main() 
{
    int shmId, semId;
    struct shared_memory *shm;

    // Criando semáforo para controlar a troca de mensagens
    semId = semget(1234, 1, 0666 | IPC_CREAT);
    semctl(semId, 0, SETVAL, 1);  // Inicializando semáforo

    // Criando memória compartilhada
    shm = criar_memoria_compartilhada(&shmId);
    shm->lida = 1;  // Inicializa o estado como "lida" para permitir o primeiro envio

    while (1) 
    {
        semaforoP(semId);  // Trava o semáforo para acessar a memória compartilhada

        if (shm->lida == 1) 
        {  // Se a mensagem anterior foi lida, enviar uma nova
            printf("Digite uma mensagem: ");
            fgets(shm->mensagem, 100, stdin);
            shm->lida = 0;  // Marca como não lida
        }

        semaforoV(semId);  // Libera o semáforo
        sleep(1);  // Aguarda 1 segundo antes de tentar enviar outra mensagem
    }

    return 0;
}