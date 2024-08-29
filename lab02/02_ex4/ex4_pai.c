#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>


#define SHM_SIZE 1024
#define KEY1 8752
#define KEY2 8753

typedef struct
{
    int value;
    int sequence;
} SharedData;

int main(void)
{
    int shmid1 = shmget(KEY1, SHM_SIZE, IPC_CREAT | 0666);
    int shmid2 = shmget(KEY2, SHM_SIZE, IPC_CREAT | 0666);
    int last_seq1 = 0, last_seq2 = 0;
    
    if (shmid1 == -1 || shmid2 == -1)
    {
        perror("shmget");
        exit(1);
    }
    
    SharedData* m1 = (SharedData*)shmat(shmid1, NULL, 0);
    SharedData* m2 = (SharedData*)shmat(shmid2, NULL, 0);
    
    if (m1 == (void*)-1 || m2 == (void*)-1) {
        perror("shmat");
        exit(1);
    }
    
    m1->sequence = 0;
    m2->sequence = 0;

    if (fork() == 0)
    {
        execl("./ex4_p1", "ex4_p1", NULL);
    }
    
    if (fork() == 0)
    {
        execl("./ex4_p2", "ex4_p2", NULL);
    }
    
    while (1)
    {
        if (m1->sequence > last_seq1 && m2->sequence > last_seq2)
        {
            printf("Produto: %d\n\n", m1->value * m2->value);
            last_seq1 = m1->sequence;
            last_seq2 = m2->sequence;
        }
        usleep(100000); // Dorme por 100ms
    }
    
    return 0;
}


/*
## Resposta ao exercicio

Inicialmente foram alocadas e anexadas duas areas de memoria, "m1" e "m2", nas quais se armazenou
a estrutura "SharedData", que armazena dois valores inteiros: um para compor a multiplicacao, o outro
para indicar qual a posicao do valor atual na sequencia de numeros gerados. Dessa forma, depois de criar
dois processos filhos, os campos de "m1" e de "m2" passam a ser atualizados a intervalos de tempo randomicos
gracas ao uso de "sleep" associado a "rand". Simultaneamente, o pai fica em loop verificando se os dois filhos
produziram valores. Se sim, exibe o produto dos valores armazenados na memoria compartilhada. Em seguida, dorme por 
100 ms e itera o loop.

Cabe mencionar que este programa corresponde a um belo exemplo de coordenacao entre multiplos processos, que se manifesta
no uso da memoria compartilhada alocada pelo pai quanto por seus filhos.
*/