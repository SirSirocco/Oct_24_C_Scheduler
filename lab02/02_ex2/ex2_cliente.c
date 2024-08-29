#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define SHM_KEY 8752
#define SHM_SIZE 1024 // Tamanho da memoria compartilhada

int main(void)
{
    int segmento;
    char *memoria_compartilhada;
 
    segmento = shmget(SHM_KEY, SHM_SIZE, S_IRUSR | S_IWUSR); // Acessando a memoria compartilhada com chave SHM_KEY
    if (segmento < 0)
    {
        perror("shmget");
        exit(1);
    }

    memoria_compartilhada = (char *)shmat(segmento, 0, 0); // Associando a memoria compartilhada ao processo
    if (memoria_compartilhada == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }
   
    printf("Mensagem do dia: %s\n", memoria_compartilhada); // Exibindo a mensagem armazenada na memoria compartilhada
    
    shmdt(memoria_compartilhada); // Desanexando a memoria compartilhada

    return 0;
}