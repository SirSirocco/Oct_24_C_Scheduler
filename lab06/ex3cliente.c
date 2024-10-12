#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_SERVIDOR "fifo_servidor"
#define FIFO_CLIENTE "fifo_cliente"

int main() 
{
    char mensagem[100];
    char buffer[100];
    int servidor_fifo, cliente_fifo;

    // Abre as FIFOs para leitura e escrita
    servidor_fifo = open(FIFO_SERVIDOR, O_WRONLY);
    cliente_fifo = open(FIFO_CLIENTE, O_RDONLY);

    if (servidor_fifo < 0 || cliente_fifo < 0)
    {
        perror("Erro ao abrir as FIFOs");
        exit(EXIT_FAILURE);
    }

    printf("Digite uma mensagem para enviar ao servidor: ");
    fgets(mensagem, sizeof(mensagem), stdin);

    // Envia a mensagem para o servidor
    write(servidor_fifo, mensagem, strlen(mensagem) + 1);

    // Aguarda a resposta do servidor
    if (read(cliente_fifo, buffer, sizeof(buffer)) > 0) 
    {
        printf("Resposta do servidor: %s\n", buffer);
    }

    close(servidor_fifo);
    close(cliente_fifo);
    return 0;
}
