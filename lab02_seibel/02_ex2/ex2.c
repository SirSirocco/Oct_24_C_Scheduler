#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // UNIx STandarD Library
#include <sys/shm.h>    // SHared Memory
#include <sys/stat.h>
#include <sys/ipc.h>    // Inter-Process Communication
#include <sys/wait.h>
#include <time.h>

#define TAM_VET 10000   // Numero de posicoes do vetor
#define NUM_FIL 2       // Numero de processos filhos (trabalhadores)
#define LIM_LOG 10      // Limite de mensagens exibidas no log

int main(void)
{
    // Cria memoria compartilhada
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
    
    shmptr = (int*)shmat(shmid, NULL, 0); // Anexa-se a memoria compartilhada

    if (shmid == -1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Preenche vetor com 5
    for (int i = 0; i < TAM_VET; i++)
        *(shmptr + i) = 5;

    for (int i = 0; i < NUM_FIL; i++) // Cria processos trabalhadores
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

            shmdt(shmptr); // Desanexa da memoria compartilhada, mas sem a liberar
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < NUM_FIL; i++) // Pai espera pelos filhos
        wait(&status);

    ref = *(shmptr); // Primeiro elemento do vetor eh valor de referencia
    printf("# VALOR DE REFERENCIA: %d\n\n", ref);

    for (int i = 1; i < TAM_VET; i++)
    {
        atual = *(shmptr + i);
        if (ref != atual)
        {
            printf("> Na posicao %4d, valor %d difere\n", i, atual); // Exibe valor atual se for divergente da referencia
            count++;

            if (count >= LIM_LOG) // Evita saturacao do log
            {
                puts("\n! Para evitar saturacao do log, nao serao exibidos os proximos divergentes\n");
                status = i + 1; // status armazena a posicao em que se parou no vetor
                break;          // Quebra loop atual e procede para o proximo, que nao exibe os valores divergentes
            }
        }
    }

    for (int i = status; i < TAM_VET; i++) // Loop que nao exibe valores divergentes
    {
        if (ref != *(shmptr + i))
            count++;
    }

    printf("* TOTAL DE DIVERGENCIAS: %d\n", count);

    shmdt(shmptr); // Desanexa da memoria compartilhada
    shmctl(shmid, IPC_RMID, NULL); // Libera memoria compartilhada com IPC_RMID

    return 0;
}
