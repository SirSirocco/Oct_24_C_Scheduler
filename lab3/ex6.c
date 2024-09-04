#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

time_t start_time;
time_t end_time;
int chamada_ativa = 0;

void inicio_chamada(int sinal) {
    if (!chamada_ativa) {
        chamada_ativa = 1;
        start_time = time(NULL); // Marca o tempo de início
        printf("Chamada iniciada.\n");
    } else {
        printf("Chamada já está em andamento.\n");
    }
}

void fim_chamada(int sinal) {
    if (chamada_ativa) {
        chamada_ativa = 0;
        end_time = time(NULL); // Marca o tempo de término
        double duracao = difftime(end_time, start_time); // Calcula a duração em segundos
        
        // Calcula o custo
        double custo;
        if (duracao <= 60) {
            custo = duracao * 0.02; // 2 centavos por segundo para os primeiros 60 segundos
        } else {
            custo = 60 * 0.02 + (duracao - 60) * 0.01; // 1 centavo por segundo após 1 minuto
        }

        printf("Chamada encerrada. Duração: %.0f segundos. Custo: R$%.2f\n", duracao, custo);
    } else {
        printf("Nenhuma chamada está em andamento.\n");
    }
}

int main() {
    // Configura os sinais
    signal(SIGUSR1, inicio_chamada); // Sinal para iniciar a chamada
    signal(SIGUSR2, fim_chamada);    // Sinal para terminar a chamada

    printf("Programa monitorando chamadas. Use SIGUSR1 para iniciar e SIGUSR2 para encerrar.\n");

    // Loop infinito para manter o programa rodando em background
    while (1) {
        pause(); // Espera por sinais
    }

    return 0;
}