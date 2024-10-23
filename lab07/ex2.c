#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>

// Definindo o tamanho do buffer
#define BUFFER_SIZE 16

// Estrutura para o buffer compartilhado
struct shared_memory 
{
    char buffer[BUFFER_SIZE];
    int count;  // Contador de caracteres no buffer
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
    *shmId = shmget(IPC_PRIVATE, sizeof(struct shared_memory), 0666 | IPC_CREAT);
    if (*shmId == -1) 
    {
        perror("Falha ao criar memória compartilhada");
        exit(1);
    }
    return (struct shared_memory*) shmat(*shmId, NULL, 0);
}

// Função para remover memória compartilhada
void remover_memoria_compartilhada(int shmId)
 {
    shmctl(shmId, IPC_RMID, NULL);
}

int main() 
{
    int shmId, semId;
    struct shared_memory *shm;

    // Criando semáforo para controlar o buffer
    semId = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    semctl(semId, 0, SETVAL, 1);  // Inicializando semáforo

    // Criando memória compartilhada
    shm = criar_memoria_compartilhada(&shmId);
    shm->count = 0;  // Inicializando o contador do buffer

    // Criando o processo concorrente
    pid_t pid = fork();

    if (pid == 0) {  // Processo filho - Impressora (Consumidor)
        while (1) 
        {
            semaforoP(semId);  // Acessa a memória compartilhada
            if (shm->count == BUFFER_SIZE) 
            {
                printf("Buffer cheio. Imprimindo: ");
                for (int i = 0; i < BUFFER_SIZE; i++) 
                {
                    putchar(shm->buffer[i]);
                }
                putchar('\n');
                shm->count = 0;  // Esvazia o buffer
            }
            semaforoV(semId);  // Libera o semáforo
            sleep(1);
        }
    } else {  // Processo pai - Leitor (Produtor)
        while (1) 
        {
            semaforoP(semId);  // Acessa a memória compartilhada
            if (shm->count < BUFFER_SIZE)
             {
                printf("Digite um caractere: ");
                char c = getchar();
                shm->buffer[shm->count] = c;
                shm->count++;
            }
            semaforoV(semId);  // Libera o semáforo
            sleep(1);
        }

        wait(NULL);  // Espera o processo filho terminar
        remover_memoria_compartilhada(shmId);
    }

    return 0;
}
