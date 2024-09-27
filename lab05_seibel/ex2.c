#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define TAM_VET 100000      // Numero de posicoes do vetor
#define NUM_THREAD 1000     // Numero de tarefas
#define COUNT_THRESH 10     // Limite de mensagens exibidas no log
#define USLEEP_T 3          // Tempo de espera (em microsegundos)

void* atualizaVetor(void* tid);

/* VARIAVEIS GLOBAIS */
unsigned long long vetor[TAM_VET];

/* FUNCOES */
int main(void)
{
    pthread_t thread[NUM_THREAD];
    int i, 
        tid,        // Thread IDentification (identificador da tarefa)
        count = 0;  // Contador de valores que diferem da referencia
    
    unsigned long long ref,
                       atual;

    for (i = 0; i < TAM_VET; i++) // Inicializa vetor
        vetor[i] = 5;
    
    for (tid = 0; tid < NUM_THREAD; tid++) // Cria tarefas
        pthread_create(thread + tid, NULL, atualizaVetor, (void*)tid);
    
    for (tid = 0; tid < NUM_THREAD; tid++) // Espera todas as tarefas terminarem
        pthread_join(thread[tid], NULL);

    ref = vetor[0];
    printf(">>> REFERENCIA: %llu\n", ref);

    for (i = 1; i < TAM_VET; i++) // Computa valores que diferem da referencia
    {
        if ((atual = vetor[i]) != ref)
        {
            printf("%-5d - Valor %llu difere da referencia\n", i, atual);

            if (++count >= COUNT_THRESH) // Evita saturacao do log
            {
                puts("\n!!! Nao serao exibidos mais valores para evitar saturacao do log");
                break;
            }
        }
    }

    for (i++; i < TAM_VET; i++) // Termina de comparar restante dos valores
    {
        if ((atual = vetor[i]) != ref)
            count++;
    }

    if (!count)
        puts("\n*** Todos os valores sao iguais a referencia");
    else
        printf("\n*** Total de diferentes: %d\n", count);

    return 0;
}

void* atualizaVetor(void* tid)
{
    for (int i = 0; i < TAM_VET; i++)
    {
        vetor[i] *= 2;
        // usleep(USLEEP_T);
        vetor[i] += 2;
    }

    pthread_exit(NULL);
}
