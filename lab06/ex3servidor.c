#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_SERVIDOR "fifo_servidor"
#define FIFO_CLIENTE "fifo_cliente"

void to_uppercase(char *str)
 {
    for (int i = 0; str[i]; i++)
    {
        str[i] = toupper(str[i]);
    }
}

int main() {
    char buffer[100];
    int servidor_fifo, cliente_fifo;

    // Abre as FIFOs para leitura e escrita
    servidor_fifo = open(FIFO_SERVIDOR, O_RDONLY);
    cliente_fifo = open(FIFO_CLIENTE, O_WRONLY);

    if (servidor_fifo < 0 || cliente_fifo < 0) {
        perror("Erro ao abrir as FIFOs");
        exit(EXIT_FAILURE);
    }

    printf("Servidor rodando em background...\n");

    // Loop infinito para processar mensagens dos clientes
    while (1) {
        if (read(servidor_fifo, buffer, sizeof(buffer)) > 0) {
            printf("Mensagem recebida do cliente: %s", buffer);
            to_uppercase(buffer); // Converte para maiúsculas
            write(cliente_fifo, buffer, strlen(buffer) + 1);
        }
    }

    close(servidor_fifo);
    close(cliente_fifo);
    return 0;
}
