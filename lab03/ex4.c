#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void loop_infinito() {
    while (1) {
        printf("Processo %d em execução\n", getpid());
        sleep(1);
    }
}

int main() {
    pid_t filho1, filho2;
    int trocas = 0;

    if ((filho1 = fork()) == 0) {
        loop_infinito();
    }

    if ((filho2 = fork()) == 0) {
        loop_infinito();
    }

    while (trocas < 10) {
        kill(filho2, SIGSTOP);
        kill(filho1, SIGCONT);
        sleep(2);

        kill(filho1, SIGSTOP);
        kill(filho2, SIGCONT);
        sleep(2);

        trocas++;
    }

    kill(filho1, SIGKILL);
    kill(filho2, SIGKILL);

    printf("Processos filho terminados após %d trocas de contexto\n", trocas);

    return 0;
}