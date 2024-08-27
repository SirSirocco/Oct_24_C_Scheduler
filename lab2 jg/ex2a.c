#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHM_KEY 8752
#define SHM_SIZE 1024 // Tamanho da memória compartilhada

int main() {
    int segmento;
    char *memoria_compartilhada;
    char mensagem[SHM_SIZE];

    
    printf("Digite a mensagem do dia: ");
    fgets(mensagem, SHM_SIZE, stdin);                                                   // Pegando a mensagem do teclado.

   
    segmento = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | S_IRUSR | S_IWUSR);            // Associa a memória compartilhada ao processo.
    if (segmento < 0) {
        perror("shmget");
        exit(1);
    }

    memoria_compartilhada = (char *)shmat(segmento, 0, 0);
    if (memoria_compartilhada == (char *)-1) {                  // Associa a memória compartilhada ao processo.
        perror("shmat");        
        exit(1);
    }

   
    strncpy(memoria_compartilhada, mensagem, SHM_SIZE);                // Copiando a mensagem para a memória compartilhada.

    printf("Mensagem armazenada na memória compartilhada.\n");

    
    shmdt(memoria_compartilhada);                             // Desanexando a memória compartilhada.

    return 0;
}