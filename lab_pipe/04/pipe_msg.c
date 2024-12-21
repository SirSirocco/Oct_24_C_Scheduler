// #define PID 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// AUXILIAR DEFINITIONS

#define error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define TRUE        1
#define READ        0
#define WRITE       1

// PARAMETRIC DEFINITIONS

#define CYCLE       60
#define NUM_FD      2
#define NUM_RDR     60
#define SIZ_BUF     64
#define T_SLP_R     2
#define T_SLP_W     (T_SLP_R / 2)

int main(void)
{
    int     fd[NUM_FD], count = 0;
    pid_t   writer, reader[NUM_RDR];
    char    buf[SIZ_BUF];

    if (pipe(fd) == -1)
        error("pipe");

    if ((writer = fork()) < 0)
        error("fork writer");

    else if (writer == 0)
    {
        while (TRUE)
        {
            sprintf(buf, "msg %d", count);
            write(fd[WRITE], buf, strlen(buf) + 1);

            count = (count + 1) % CYCLE;

            sleep(T_SLP_W);
        }
    }

    for (int i = 0; i < NUM_RDR; i++)
    {
        if ((reader[i] = fork()) < 0)
        {
            sprintf(buf, "fork reader %d", i);
            error(buf);
        }

        else if (reader[i] == 0)
        {
            #ifdef PID
                reader[i] = getpid();

            #else
                reader[i] = i;

            #endif

            while (TRUE)
            {
                read(fd[READ], buf, SIZ_BUF);
                printf("PID %d - %s\n", reader[i], buf);

                sleep(T_SLP_R);
            }
        }
    }

    while (TRUE); // Loops forever

    return EXIT_SUCCESS;
}
