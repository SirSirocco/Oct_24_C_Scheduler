#include <stdio.h>      // printf
#include <stdlib.h>     // exit
#include <signal.h>     // Macros SIG
#include <sys/time.h>   // timeval
#include <sys/wait.h>   // pid_t
#include <unistd.h>     // fork

#define TRUE 1
#define NUM_FIL 3
#define EVER ;;

/* TABELA DE TEMPOS (em segundos) */
#define T_INI_P1    5
#define T_FIN_P1    25
#define T_INI_P2    45
#define T_FIN_P2    0       // 0 = (45 + 15) % 60

void escalona_exibe(pid_t* pid, int i_stop, int i_cont);

int main(void)
{
    pid_t pid[NUM_FIL]; // Armazena PIDs dos processos filhos
    struct timeval instante;

    for (int i = 0; i < NUM_FIL; i++)
    {
        if ((pid[i] = fork()) < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid[i] == 0) // Filho
            for (EVER);
    }
    // Pai
    for (int i = 0; i < NUM_FIL; i++) // Coloca todos os filhos em espera
        escalona_exibe(pid, i, -1);

    // Espera ate
    do
    {
        gettimeofday(&instante, NULL);
    } while (instante.tv_sec % 60);

    escalona_exibe(pid, -1, 2);

    while (TRUE)
    {
        gettimeofday(&instante, NULL);

        switch (instante.tv_sec % 60)
        {
        case T_FIN_P2:
            escalona_exibe(pid, 1, 2);
            break;
        case T_INI_P1:
            escalona_exibe(pid, 2, 0);
            break;
        case T_FIN_P1:
            escalona_exibe(pid, 0, 2);
            break;
        case T_INI_P2:
            escalona_exibe(pid, 2, 1);
            break;
        default:
        }
    }
}

void escalona(pid_t* pid, int i_stop, int i_cont)
{
    if (i_stop > -1)
        kill(pid[i_stop], SIGSTOP);
    if (i_cont > -1)
        kill(pid[i_cont], SIGCONT);
}

void exibe(int i_stop, int i_cont)
{
    if (i_stop > -1)
        printf("Processo %d parado\n", i_stop + 1);
    if (i_cont > -1)
        printf("Processo %d continuado\n", i_cont + 1);
}

void escalona_exibe(pid_t* pid, int i_stop, int i_cont)
{
    escalona(pid, i_stop, i_cont);
    exibe(i_stop, i_cont);
}
