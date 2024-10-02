#include <stdio.h>
#include <pthread.h>

#define VETOR_SIZE 10000
#define NUM_TRABALHADORES 10

int vetor[VETOR_SIZE];
int soma_parcial[NUM_TRABALHADORES];

// Funcao que cada thread ira executar
void* trabalhador(void* arg) {
    int id = *(int*)arg;
    int inicio = id * (VETOR_SIZE / NUM_TRABALHADORES);
    int fim = inicio + (VETOR_SIZE / NUM_TRABALHADORES);
    int soma = 0;

    for (int i = inicio; i < fim; i++) {
        vetor[i] *= 2;  // Multiplica por 2
        soma += vetor[i];  // Soma os valores
    }

    soma_parcial[id] = soma;  // Salva a soma parcial
    pthread_exit(NULL);
}

int main() {
    // Inicializando o vetor com valor 5
    for (int i = 0; i < VETOR_SIZE; i++) {
        vetor[i] = 5;
    }

    pthread_t threads[NUM_TRABALHADORES];
    int ids[NUM_TRABALHADORES];

    // Criando os trabalhadores (threads)
    for (int i = 0; i < NUM_TRABALHADORES; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, trabalhador, (void*)&ids[i]);
    }

    // Aguardando os trabalhadores terminarem
    for (int i = 0; i < NUM_TRABALHADORES; i++) {
        pthread_join(threads[i], NULL);
    }

    // Somando as parcelas
    int soma_total = 0;
    for (int i = 0; i < NUM_TRABALHADORES; i++) {
        soma_total += soma_parcial[i];
    }

    // Exibindo o resultado final
    printf("Soma total: %d\n", soma_total);

    return 0;
}
