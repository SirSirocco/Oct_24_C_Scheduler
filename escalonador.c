#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>

#define TRUE 1
#define NUM_FIL 3
#define FILE_PATH "./filho" // Usamos "./" para que os filhos compartilhem o stdout do pai

int main(void)
{
    int i, shmid;
    pid_t pid[NUM_FIL], pid_meu;
    struct timeval instante;
    unsigned long long* shmptr;

    shmid = shmget(IPC_PRIVATE, sizeof(unsigned long long), IPC_CREAT | S_IRWXU);

    if (shmid == -1)
    {
        perror("shmid");
        exit(EXIT_FAILURE);
    }

    shmptr = (unsigned long long*)shmat(shmid, NULL, 0);

    if (shmptr == -1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    *shmptr = 0ull;

    for (i = 0; i < NUM_FIL; i++)
    {
        if ((pid[i] = fork()) < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid[i] == 0)
        {
            pid_meu = getpid();

            while (TRUE)
            {
                *shmptr += 5;
                printf("%5lld - PID %d\n", *shmptr, pid_meu);
                sleep(5);
            }
        }
    }

    for (i = 0; i < NUM_FIL; i++) // Coloca todos os filhos em espera
        kill(pid[i], SIGSTOP);

    while (TRUE)
    {
        gettimeofday(&instante, NULL);

        switch (instante.tv_sec % 60)
        {
            case 0:
                kill(pid[1], SIGSTOP);
                kill(pid[2], SIGCONT);
                break;
            
            case 5:
                kill(pid[2], SIGSTOP);
                kill(pid[0], SIGCONT);
                break;
            
            case 25:
                kill(pid[0], SIGSTOP);
                kill(pid[2], SIGCONT);
                break;

            case 45:
                kill(pid[2], SIGSTOP);
                kill(pid[1], SIGCONT);
                break;

            default:
        }
    }
}

