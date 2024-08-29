#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>


#define SHM_KEY 8752
#define SHM_SIZE 1024 // Tamanho da memoria compartilhada

int main(void)
{
    int segmento;
    char *memoria_compartilhada;
    char mensagem[SHM_SIZE];
    
    printf("Digite a mensagem do dia: ");
    fgets(mensagem, SHM_SIZE, stdin); // Pegando a mensagem do teclado
   
    segmento = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | S_IRUSR | S_IWUSR); // Associa a memoria compartilhada ao processo
    if (segmento < 0)
    {
        perror("shmget");
        exit(1);
    }

    memoria_compartilhada = (char *)shmat(segmento, 0, 0); // Associa a memoria compartilhada ao processo
    if (memoria_compartilhada == (char *)-1)
    {                  
        perror("shmat");        
        exit(1);
    }
   
    strncpy(memoria_compartilhada, mensagem, SHM_SIZE); // Copiando a mensagem para a memoria compartilhada

    printf("Mensagem armazenada na memória compartilhada.\n");
    
    shmdt(memoria_compartilhada); // Desanexando a memoria compartilhada.

    return 0;
}


/*
## Resposta ao exercicio

Inicialmente, com "shmget" e "shmat", o programa servidor aloca memoria compartilhada e a preenche
com a mensagem do dia, obtida do teclado com "fgets" e "stdin". Ao final, por meio de "shmdt", apenas
desanexa tal area do processo atual, mas nao a remove. Por isso, usando da mesma chave de acesso (8752) que o
servidor, o programa cliente consegue acessar a mesma area de memoria e exibir a mensagem do dia nela contida.
*/