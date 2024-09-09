#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#define EVER ;;

void intHandler(int sinal);
void quitHandler(int sinal);

int main(void) {
    void (*p)(int);  // ponteiro para função que recebe int como parâmetro

    p = signal(SIGINT, intHandler);
    printf("Endereco do manipulador anterior %p\n", p);

    p = signal(SIGQUIT, quitHandler);
    printf("Endereco do manipulador anterior %p\n", p);

    puts("Ctrl-C desabilitado. Use Ctrl-\\ para terminar");

    for(EVER);

    return 0;
}

void intHandler(int sinal) {
    printf("Você pressionou Ctrl-C (%d)\n", sinal);
}

void quitHandler(int sinal) {
    printf("Terminando o processo...\n");
    exit(0);
}


/* Perceba que no programa com as chamadas de sinais você executa o previsto com o ctrl-c e cntrl-\ no terminal, e sem, não. Respectivamente os previstos são aparecer 
no terminal "Você pressionou Ctrl-C" e acabar a execução do programa.*/


