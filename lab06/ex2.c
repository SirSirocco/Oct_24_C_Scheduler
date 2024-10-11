#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

#define FIFO_NAME "minhaFifo"

int main() {
    // Cria a FIFO se ela ainda não existir
    if (mkfifo(FIFO_NAME, 0666) == -1)
    {
        perror("Erro ao criar FIFO");
        exit(EXIT_FAILURE);
    }

    // Cria dois processos filhos
    pid_t pid1 = fork();
    if (pid1 == 0) 
    {
        // Primeiro processo filho
        int fifo = open(FIFO_NAME, O_WRONLY);
        char mensagem1[] = "Mensagem do filho 1\n";
        write(fifo, mensagem1, strlen(mensagem1));
        close(fifo);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) 
    {
        // Segundo processo filho
        int fifo = open(FIFO_NAME, O_WRONLY);
        char mensagem2[] = "Mensagem do filho 2\n";
        write(fifo, mensagem2, strlen(mensagem2));
        close(fifo);
        exit(0);
    }

    // Processo pai: espera pelos filhos
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    // Processo pai lê as mensagens da FIFO
    int fifo = open(FIFO_NAME, O_RDONLY);
    char buffer[128];
    while (read(fifo, buffer, sizeof(buffer)) > 0) 
    {
        printf("Mensagem recebida: %s", buffer);
    }
    close(fifo);

    // Remove a FIFO após o uso
    unlink(FIFO_NAME);
    return 0;
}
