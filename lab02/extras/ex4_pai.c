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

int main(void)
{
    int * m[2],
        mkey[2] = {M1, M2},
        // segmento[2],
        // status,
        pid,
        tam = sizeof(mkey) / sizeof(mkey[0]);

    char* file_name = "ex4_filho",
        * argv[2] =
    {
        file_name,
        NULL
    };

    for (int i = 0; i < tam; i++)
    {
        shmget(mkey[i], 2 * sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
        m[i] = shmat(mkey[i], NULL, 0);
    }

    for (int j = 0; j < tam; j++)
    {
        if ((pid = fork()) < 0) // Erro
        {
            puts("Erro ao criar processo");
            exit(EXIT_FAILURE);
        }

        else if (pid == 0) // Filho
        {
            char str[2] = { j, '\0'};
            argv[1] = str;
            execv(file_name, argv);
        }

        else // Pai
        {

        }
    }

    printf("Ola\n\n");

    while (!*(m[0] + 1) || !*(m[1] + 1))
    {
        if (*(m[0] + 1) == TRUE)
        {
            printf("valor do filho 1 recebido: %d\n", *m[0]);
            sleep(1);
        }

        if (*(m[1] + 1) == TRUE)
        {
            printf("valor do filho 2 recebido: %d\n", *m[0]);
            sleep(1);
        }
    }

    printf("valor do filho 1: %d\n", *m[0]);
    printf("valor do filho 2: %d\n", *m[1]);
    printf("produto dos valores: %d\n", (*m[0]) * (*m[1]));

    for (int i = 0; i < tam; i++)
    {
        shmdt(m[i]);
        shmctl(mkey[i], IPC_RMID, NULL);
    }

    return 0;
}
