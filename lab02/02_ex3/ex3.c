#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#define SHM_KEY 12345
#define ARRAY_SIZE 20
#define NUM_PROCESSES 4

int main() {
    int segmento, pid, chave, status;
    int *vetor;
    int part_size = ARRAY_SIZE / NUM_PROCESSES;
    
    
    segmento = shmget(SHM_KEY, ARRAY_SIZE * sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
    if (segmento < 0) {
        perror("shmget");
        exit(1);
    }

   
    vetor = (int *)shmat(segmento, 0, 0);
    if (vetor == (int *)-1) {
        perror("shmat");
        exit(1);
    }

                                                            // Preenche o vetor com valores inteiros desordenados
    for (int i = 0; i < ARRAY_SIZE; i++) {
        vetor[i] = rand() % 100;                              // Valores aleatórios entre 0 e 99
    }

    // Exibe o vetor gerado
    printf("Vetor: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    
    printf("Digite a chave a ser buscada: ");
    scanf("%d", &chave);

                                            // Cria processos filhos
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if ((pid = fork()) < 0) {
            perror("Erro na criacao do processo");
            exit(1);
        } else if (pid == 0) {                                                      // Código do processo filho
            int start = i * part_size;
            int end = (i == NUM_PROCESSES - 1) ? ARRAY_SIZE : start + part_size;

            
            for (int j = start; j < end; j++) {                                         // Busca a chave na parte designada do vetor
                if (vetor[j] == chave) {
                    printf("Processo %d encontrou a chave %d na posição %d\n", i, chave, j);
                    exit(0);
                }
            }

            
            printf("Processo %d não encontrou a chave\n", i);
            exit(0);
        }
    }

    
    for (int i = 0; i < NUM_PROCESSES; i++) {
        wait(&status);
    }

  
    shmdt(vetor);
    shmctl(segmento, IPC_RMID, 0);

    return 0;
}