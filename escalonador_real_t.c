#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

#define TRUE 1
#define NUM_FIL 3
#define FILE_PATH "./filho" // Usamos "./" para que os filhos compartilhem o stdout do pai
#define P_INI 1             // Indice do processo no vetor de PIDs que dara inicio ao ciclo

/* TABELA DE TEMPOS (em segundos) */
#define T_INI_P1    5
#define T_FIN_P1    (5 + 20)
#define T_INI_P2    45
#define T_FIN_P2    0       // 0 = (45 + 15) % 60

int main(void)
{
    int i;
    pid_t pid[NUM_FIL];     // Vetor de PIDs
    struct timeval instante;

    for (i = 0; i < NUM_FIL; i++)
    {
        if ((pid[i] = fork()) < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid[i] == 0)
            execvp("./filho", NULL);
    }

    for (i = 0; i < NUM_FIL; i++) // Coloca todos os filhos em espera
        kill(pid[i], SIGSTOP);

    i = P_INI;

    alarm()

    while (TRUE)
    {
        gettimeofday(&instante, NULL);

        switch (instante.tv_sec % 60)
        {
            case T_FIN_P2:
                kill(pid[i], SIGSTOP);
                i = (i + 1) % NUM_FIL;
                kill(pid[i], SIGCONT);
                break;
            
            case T_INI_P1:
            case T_FIN_P1:
            case T_INI_P2:
                kill(pid[i], SIGSTOP);
                i = (i + 2) % NUM_FIL;
                kill(pid[i], SIGCONT);
                break;

            default:
        }
    }
}

