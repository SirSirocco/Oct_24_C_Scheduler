#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define EVER ;;

void intHandler(int sinal);
void quitHandler(int sinal);

int main(void)
{
    void (*p)(int);

    puts("Ctrl-C nao interrompera o programa");
    puts("Use Ctrl-\\ para interromper o programa");

    p = signal(SIGINT, intHandler);
    printf("Endereco do manipulador anterior %p\n", p);

    p = signal(SIGQUIT, quitHandler);
    printf("Endereco do manipulador anterior %p\n", p);

    for(EVER);
}

void intHandler(int sinal)
{
    printf("Voce pressiounou ctrl-C (%d)\n", sinal);
}

void quitHandler(int sinal)
{
    puts("Terminando o programa...");
    exit(EXIT_SUCCESS);
}