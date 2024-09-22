#include <stdio.h>      // printf, puts
#include <stdlib.h>     // exit
#include <signal.h>     // Macros SIG, kill
#include <sys/time.h>   // timeval
#include <sys/wait.h>   // pid_t
#include <unistd.h>     // fork

#define TRUE 1
#define NUM_FIL 3       // Numero de processos (filhos)
#define EVER ;;

/* TABELA DE TEMPOS (em segundos) */
#define T_INI_P1    5       // Tempo de inicio do processo 1
#define T_FIN_P1    25      // Tempo de fim    do processo 1
#define T_INI_P2    45      // Tempo de inicio do processo 2
#define T_FIN_P2    0       // Tempo de fim    do processo 2 ------> 0 = (45 + 15) % 60


// Enumerado dos possiveis estados de um processo
typedef enum estado
{
    INATIVO,
    ATIVO
} Estado;

// Representa os processos
// Agrega vetor de PIDs e de estados
typedef struct processo
{
    pid_t pid[NUM_FIL];
    Estado estado[NUM_FIL];
} Processo;


void escalona_exibe(Processo* processo, int i_stop, int i_cont, int secs);
void verifica_escalona_exibe(Processo* processo, int i_stop, int i_cont, int secs);


int main(void)
{
    Processo processo;
    struct timeval instante;
    int secs = 0;

    for (int i = 0; i < NUM_FIL; i++)
    {
        if ((processo.pid[i] = fork()) < 0) // Erro
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (processo.pid[i] == 0) // Filho
            for (EVER);
    }

    // Pai
    for (int i = 0; i < NUM_FIL; i++) // Coloca todos os filhos em espera
        escalona_exibe(&processo, i, -1, secs);

    puts("Aguarde ate a sincronizacao.");
    do // Sincronizacao: espera ate inicio do novo minuto (secs == 0)
    {
        gettimeofday(&instante, NULL);
    } while ((secs = (instante.tv_sec % 60)));

    escalona_exibe(&processo, -1, 2, secs);

    while (TRUE)
    {
        gettimeofday(&instante, NULL);

        switch ((secs = (instante.tv_sec % 60)))
        {
        case T_FIN_P2:
            verifica_escalona_exibe(&processo, 1, 2, secs); // STOP P2 CONT P3
            break;
        case T_INI_P1:
            verifica_escalona_exibe(&processo, 2, 0, secs); // STOP P3 CONT P1
            break;
        case T_FIN_P1:
            verifica_escalona_exibe(&processo, 0, 2, secs); // STOP P1 CONT P3
            break;
        case T_INI_P2:
            verifica_escalona_exibe(&processo, 2, 1, secs); // STOP P3 CONT P2
            break;
        default:
        }
    }
}

// Interrompe processo com indice i_stop e continua processo com indice i_cont
// Atualiza estados dos processos
// Se indice menor que 0, ignora
void escalona(Processo* processo, int i_stop, int i_cont)
{
    if (i_stop > -1)
    {
        kill(processo->pid[i_stop], SIGSTOP);
        processo->estado[i_stop] = INATIVO;
    }
    if (i_cont > -1)
    {
        kill(processo->pid[i_cont], SIGCONT);
        processo->estado[i_cont] = ATIVO;
    }
}

// Exibe o processo que foi interrompido e o que foi continuado juntamente com o instante em segundos
// Se indice menor que 0, ignora
void exibe(int i_stop, int i_cont, int secs)
{
    if (i_stop > -1)
        printf("%02d - Processo %d parado\n", secs, i_stop + 1);
    if (i_cont > -1)
        printf("%02d - Processo %d continuado\n", secs, i_cont + 1);
}

// Wrapper das funcoes escalona e exibe
void escalona_exibe(Processo* processo, int i_stop, int i_cont, int secs)
{
    escalona(processo, i_stop, i_cont);
    exibe(i_stop, i_cont, secs);
}

// Wrapper da funcao escalona_exibe
// Apenas executa se o processo a ser interrompido esta ativo e o processo a ser continuado esta inativo
// Supoe indices maiores ou iguais a 0
void verifica_escalona_exibe(Processo* processo, int i_stop, int i_cont, int secs)
{
    if (processo->estado[i_stop] == ATIVO && processo->estado[i_cont] == INATIVO)
        escalona_exibe(processo, i_stop, i_cont, secs);
}
