#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#define EVER ;;
#define TEMPO 3 // Em segundos

void usrHandler(int sinal);
void killHandler(int sinal);

int main(void)
{
    pid_t pid;
    int status;

    if ((pid = fork()) < 0) // Erro
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) // Filho
    {
        signal(SIGUSR1, usrHandler);    // Filho recebe sinal teste
        signal(SIGKILL, killHandler);   // Filho tenta escapar da morte
        for (EVER);
    }
    else // Pai
    {
        sleep(TEMPO);
        kill(pid, SIGUSR1);
        
        sleep(TEMPO);
        kill(pid, SIGKILL); // Mata processo filho
        
        sleep(TEMPO);
        kill(pid, SIGUSR1);

        waitpid(pid, &status, 0); // Atualiza status
        /*
            Eh necessario atualizar status, do contrario se usarah lixo
            para determinar se o processo foi morto por sinal, o que produzirah
            comportamento imprevisivel.
        */

        if (WIFSIGNALED(status)) // Verifica que filho foi morto por sinal
            puts("Ninguem escapa da morte... ate mesmo um processo.");
    }

    return 0;
}

// Trata SIGUSR1 (10)
void usrHandler(int sinal)
{
    puts("Recebido sinal de usuario 1");
}

// Trata (ou, ao menos, tenta) SIGKILL (9)
void killHandler(int sinal)
{
    puts("Tentaram me matar, mas escapei da morte.");
}
