#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() 
{
    int fifo;
    char buffer[100];
    
    fifo = open("minhaFifo", O_RDONLY);
    if (fifo < 0) 
    {
        perror("Erro ao abrir FIFO para leitura");
        return 1;
    }

    printf("Esperando por dados...\n");
    while (read(fifo, buffer, sizeof(buffer)) > 0) 
    {
        printf("Recebido: %s\n", buffer);
    }

    close(fifo);
    return 0;
}
