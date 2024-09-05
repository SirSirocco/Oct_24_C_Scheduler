#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[])
{
    int segmento, *p, id, pid, status;
    // aloca a memória compartilhada
    segmento = shmget (IPC_PRIVATE, sizeof (int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    // associa a memória compartilhada ao processo
    p = (int *) shmat (segmento, 0, 0); // comparar o retorno com -1
    *p = 8752;
    if ((id = fork()) < 0)
    {
        puts ("Erro na criação do novo processo");
        exit (-2);
    }
    else if (id == 0)
    {
        *p += 5;
        printf ("Pid do filho   = %d\n", getpid());
        printf ("Processo filho = %d\n\n", *p);
    }
    else
    {
        pid = wait (&status);
        *p += 10;
        printf ("Pid do pai   = %d\n", getpid());
        printf ("Processo pai = %d\n\n", *p);
        // libera a memória compartilhada
        shmctl (segmento, IPC_RMID, 0);
    }

    // libera a memória compartilhada do processo
    shmdt (p);
    // libera a memória compartilhada
    // shmctl (segmento, IPC_RMID, 0);

    return 0;
}
