#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handler(int sinal) {
    printf("Sinal %d recebido\n", sinal);
}

int main(void) {
    // Tentativa de interceptar SIGKILL
    if (signal(SIGKILL, handler) == SIG_ERR) {
        printf("Erro: Não é possível interceptar SIGKILL.\n");
    }

    // Interceptando SIGTERM (só para comparação)
    if (signal(SIGTERM, handler) == SIG_ERR) {
        printf("Erro: Não é possível interceptar SIGTERM.\n");
    }

    printf("Programa em execução. Tente enviar SIGKILL ou SIGTERM.\n");

    while (1) {
        // Loop infinito para manter o programa rodando
    }

    return 0;
}


/* É impossível interceptar o SIGKILL, o sistema não deixa. */