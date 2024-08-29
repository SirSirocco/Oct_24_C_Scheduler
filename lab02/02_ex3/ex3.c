#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_KEY 12345
#define ARRAY_SIZE 20
#define NUM_PROCESSES 4

int main(void)
{
    int segmento, pid, chave, status;
    int* vetor;
    int part_size = ARRAY_SIZE / NUM_PROCESSES, inicio, fim;
    
    segmento = shmget(SHM_KEY, ARRAY_SIZE * sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
    if (segmento < 0)
    {
        perror("shmget");
        exit(1);
    }

    vetor = (int *)shmat(segmento, 0, 0);
    if (vetor == (int *)-1)
    {
        perror("shmat");
        exit(1);
    }

    // Preenche o vetor com valores inteiros desordenados
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        vetor[i] = rand() % 100; // Valores aleatorios entre 0 e 99
    }

    // Exibe o vetor gerado
    printf("Vetor: ");
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");
    
    printf("Digite a chave a ser buscada: ");
    scanf("%d", &chave);

    // Cria processos filhos
    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        if ((pid = fork()) < 0)
        {
            perror("Erro na criacao do processo");
            exit(1);
        }
        else if (pid == 0) // Filho
        {
            inicio = i * part_size;
            fim = (i == NUM_PROCESSES - 1) ? ARRAY_SIZE : inicio + part_size;

            for (int j = inicio; j < fim; j++)
            {   // Busca a chave na parte designada do vetor
                if (vetor[j] == chave)
                {
                    printf("Processo %d encontrou a chave %d na posição %d\n", i, chave, j);
                    exit(EXIT_SUCCESS);
                }
            }
            
            printf("Processo %d não encontrou a chave\n", i);
            exit(EXIT_SUCCESS);
        }
    }
    
    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        wait(&status);
    }

    shmdt(vetor); // Desanexa memoria do processo atual
    shmctl(segmento, IPC_RMID, 0); // Libera memoria do segmento

    return 0;
}


/*
## Resposta ao exercicio

Com, respectivamente, "shmget" e "shmat", o processo pai aloca e anexa uma area de memoria compartilhada (vetor),
que sera preenchida com 20 inteiros aleatorios em uma faixa de 0 a 99. Depois de exibir-se o vetor, obtem-se via
input o valor a ser procurado. Em seguida, o pai cria 4 processos filhos, que farao cada qual uma busca
sequencial por sua parcela de memoria a ser varrida (isto é, 20 / 4 = 5 inteiros). Caso o encontrem, indicam 
a posicao em que foi achado; do contrario, indicam nao o ter encontrado. A seguir, finalizam com "exit".
Ao final, o pai desanexa e libera a memoria compartilhada com "shmdt" e "shmctl" (este ultimo por intermedio da flag IPC_RMID).
*/