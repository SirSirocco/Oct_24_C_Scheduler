#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // UNIx STandarD Library
#include <sys/shm.h>    // SHared Memory
#include <sys/stat.h>
#include <sys/ipc.h>    // Inter-Process Communication
#include <sys/wait.h>
#include <time.h>

#define TAM_VET 10000
#define NUM_FIL 2
#define LIM_LOG 10

int main(void)
{
    int shmid = shmget(IPC_PRIVATE, TAM_VET * sizeof(int), IPC_CREAT | S_IRWXU),
        *shmptr,
        pid,
        status,
        ref,
        atual,
        count = 0;
    
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

    for (int i = 0; i < NUM_FIL; i++)
    {
        if ((pid = fork()) < 0) // Falha
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) // Filho
        {   
            for (int j = 0; j < TAM_VET; j++)
            {
                *(shmptr + j) *= 2;
                usleep(100); // Tenta forcar a descoordenacao de processos
                *(shmptr + j) += 2;
            }

            shmdt(shmptr);
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < NUM_FIL; i++) // Pai espera pelos filhos
        wait(&status);

    ref = *(shmptr);
    printf("# VALOR DE REFERENCIA: %d\n\n", ref);

    for (int i = 1; i < TAM_VET; i++)
    {
        atual = *(shmptr + i);
        if (ref != atual)
        {
            printf("> Na posicao %4d, valor %d difere\n", i, atual);
            count++;

            if (count >= LIM_LOG) // Evita saturacao do log
            {
                puts("\n! Para evitar saturacao do log, nao serao exibidos os proximos divergentes\n");
                status = i + 1;
                break;
            }
        }
    }

    for (int i = status; i < TAM_VET; i++)
    {
        if (ref != *(shmptr + i))
            count++;
    }

    printf("* TOTAL DE DIVERGENCIAS: %d\n", count);

    shmdt(shmptr);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
