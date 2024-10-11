#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() 
{
    int fifo;
    char mensagem[100];

    fifo = open("minhaFifo", O_WRONLY);
    if (fifo < 0) 
    {
        perror("Erro ao abrir FIFO para escrita");
        return 1;
    }

    printf("Digite uma mensagem para enviar: ");
    while (fgets(mensagem, sizeof(mensagem), stdin) != NULL) {
        write(fifo, mensagem, strlen(mensagem) + 1);
    }

    close(fifo);
    return 0;
}