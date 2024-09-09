#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define KEY_ID 7000     // Identificador da memoria a ser anexada
#define SHM_SIZE 4096   // Tamanho minimo da memoria a ser anexada

int main(void)
{
    // Nao foi passado IPC_CREAT, porque memoria ja tinha sido criada pelo programa escritor
    int shmid = shmget(KEY_ID, SHM_SIZE, S_IRWXU);
    char* shmptr;

    if (shmid == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    shmptr = (char*)shmat(shmid, NULL, 0); // Anexa-se a memoria compartilhada

    if (shmptr == -1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("Mesagem do dia recebida: %s\n", shmptr);

    shmdt(shmptr); // Desanexa da memoria
    shmctl(shmid, IPC_RMID, NULL); // Libera memoria

    return 0;
}
