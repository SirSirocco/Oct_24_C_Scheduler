#include <stdio.h>
#include <pthread.h>

#define NUM_THREAD 100                      // Numero de tarefas trabalhadoras
#define TAM_VET 100000                      // Numero de posicoes do vetor
#define TAM_THREAD (TAM_VET / NUM_THREAD)   // Numero de posicoes atualizadas por cada trabalhadora

void* atualizaVetorSoma(void* tid);

/* VARIAVEIS GLOBAIS */
unsigned long long vetor[TAM_VET],
                   soma = 0;

/* FUNCOES */
int main(void)
{
    pthread_t thread[NUM_THREAD];

    for (int i = 0; i < TAM_VET; i++) // Inicializa vetor
        vetor[i] = 5;

    for (int tid = 0; tid < NUM_THREAD; tid++) // Cria tarefas
        pthread_create(thread + tid, NULL, atualizaVetorSoma, (void*)tid);

    for (int tid = 0; tid < NUM_THREAD; tid++) // Espera cada tarefa terminar e exibe o estado de "soma"
    {
        pthread_join(thread[tid], NULL);
        printf("* Thread %-5d - Soma: %llu\n", tid, soma);
    }

    printf(">>> Soma total: %llu\n", soma);

    return 0;
}

// Rotina a ser executada pelas threads
// Multiplica cada entrada de "vetor" por 2 e adiciona o valor atualizado a "soma"
void* atualizaVetorSoma(void* tid)
{
    int n = (int)tid;
    for (int i = n * TAM_THREAD; i < (n + 1) * TAM_THREAD; i++)
        soma += vetor[i] *= 2; // Atualiza "vetor" e depois incrementa "soma"
    pthread_exit(NULL);
}
