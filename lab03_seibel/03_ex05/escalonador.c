#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_FIL 2           // Numero de processos filhos
#define FILE_PATH "./filho" // Path do programa a ser executado (deve conter "./" para compartilhar mesmo stdout)
#define ESCLN_T 1           // Em segundos
#define ALRM_T 15           // Em segundos

void alarmHandler(int sinal);

pid_t pid[NUM_FIL];

int main(void)
{
    int i;

    for (i = 0; i < NUM_FIL; i++)
    {
        if ((pid[i] = fork()) < 0) // Erro
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid[i] == 0) // Filho
            execvp(FILE_PATH, NULL);
    }
    // Pai
    alarm(ALRM_T);                  // Prepara alarme
    signal(SIGALRM, alarmHandler);  // Acionado quando alarme soar

    for (i = 0; i < NUM_FIL; i++)   // Pausa todos os filhos
        kill(pid[i], SIGSTOP);

    while (1)
    {
        i %= NUM_FIL;               // Percorre ciclicamente os filhos
        kill(pid[i], SIGCONT);      // Continua filho atual
        sleep(1);                   // Espera 1 segundo
        kill(pid[i++], SIGSTOP);    // Pausa filho atual, depois atualiza filho
    }
}

// Trata o sinal de alarme SIGALRM (14)
void alarmHandler(int sinal)
{
    int status;

    for (int i = 0; i < NUM_FIL; i++)
        kill(pid[i], SIGKILL); // Faz matar todos os filhos

    for (int i = 0; i < NUM_FIL; i++)
    {
        waitpid(pid[i], &status, 0);
        if (WIFSIGNALED(status)) // Verifica que foram mortos
            printf("PID %d finalizado com sucesso\n", pid[i]);
    }

    puts("Fim do escalonamento");
    exit(EXIT_SUCCESS);
}
