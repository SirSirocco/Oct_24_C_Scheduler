#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // UNIx STandarD Library
#include <sys/shm.h>    // SHared Memory
#include <sys/stat.h>
#include <sys/ipc.h>    // Inter-Process Communication
#include <sys/wait.h>

#define TAM_VET 10000
#define NUM_FIL 10

int main(void)
{
    // A soma sera armazenada no (TAM_VET + 1) elmento
    int shmid = shmget(IPC_PRIVATE, (TAM_VET + 1) * sizeof(int), IPC_CREAT | S_IRWXU),
        *shmptr,
        pid,
        status;
    
    if (shmid == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    
    shmptr = (int*)shmat(shmid, NULL, 0);

    if (shmid == -1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Preenche vetor com 5
    for (int i = 0; i < TAM_VET; i++)
        *(shmptr + i) = 5;

    *(shmptr + TAM_VET) = 0; // Soma inicial recebe 0

    for (int i = 0; i < NUM_FIL; i++)
    {
        if ((pid = fork()) < 0) // Falha
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) // Filho
        {   
            for (int j = i * (TAM_VET / NUM_FIL); j < (i + 1) * (TAM_VET / NUM_FIL); j++) // Acessa diferentes secoes do vetor em funcao do numero do filho
            {
                *(shmptr + j) *= 2;
                *(shmptr + TAM_VET) += *(shmptr + j);
            }

            shmdt(shmptr); // Desanexa da memoria compartilhada, mas sem a liberar
            exit(EXIT_SUCCESS);
        }
    }
    
    for (int i = 0; i < NUM_FIL; i++) // Pai espera filhos terminarem e exibe soma parcial a cada filho que termina
    {
        wait(&status);
        printf("Soma parcial %d: %d\n", i, *(shmptr + TAM_VET));
    }

    printf("Soma total: %d\n", *(shmptr + TAM_VET));
    shmdt(shmptr); // Desanexa da memoria compartilhada
    shmctl(shmid, IPC_RMID, NULL); // Libera memoria compartilhada com IPC_RMID

    return 0;
}
