#include <math.h>
#include <stdlib.h>     // NULL
#include <stdio.h>      // printf
#include <sys/ipc.h>    // Inter-Process Communicaton -> IPC flags
#include <sys/shm.h>    // Funcoes com prefixo "shm" (Shared Memory)
#include <sys/stat.h>   // USR
#include <sys/wait.h>   // waitpid
#include <time.h>
#include <unistd.h>     // fork

#define M1 8572
#define M2 8573
#define TRUE 1

int main(int argc, char** argv)
{
    printf("entrei %s\n\n", argv[1]);
    int *m[2] = { NULL, NULL },
        mkey[2] = {M1, M2};

    int num_filho = atoi(argv[1]);

    // Para cima ok
    
    shmat(mkey[num_filho], NULL, 0);

    sleep(rand() % 5 + 1); // sleep randomico

    *m[num_filho] = 1 + rand();

    *(m[num_filho] + 1) = TRUE;
    
    shmdt(m[num_filho]);

    exit(0);
}
