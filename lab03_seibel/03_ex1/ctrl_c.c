#include <stdio.h>
#include <stdlib.h>
#include <signal.h>     // Flags SIG e funcao signal

#define EVER ;;

void intHandler(int sinal);
void quitHandler(int sinal);

/* REMOCAO DE SIGNAL */
/*
    Se as chamadas de signal forem comentadas, serao aplicados os
    tratamentos default (SIG_DFL). Neste caso, SIGINT terminarah o
    programa, ao passo que SIGQUIT, alem de o terminar, produzirah
    um core dump.
*/

int main(void)
{
    void (*p)(int);

    puts("Ctrl-C nao interrompera o programa");
    puts("Use Ctrl-\\ para interromper o programa");

    // p = signal(SIGINT, intHandler);
    printf("Endereco do manipulador anterior %p\n", p); // Exibe o endereco da funcao anterior retornado por signal

    // p = signal(SIGQUIT, quitHandler);
    printf("Endereco do manipulador anterior %p\n", p);

    for (EVER);
}

// Trata SIGINT (Ctrl-C)
void intHandler(int sinal)
{
    printf("Voce pressiounou ctrl-C (%d)\n", sinal);
}

// Trata SIGQUIT (Ctrl-\)
void quitHandler(int sinal)
{
    puts("Terminando o programa...");
    exit(EXIT_SUCCESS);
}
