#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void fpeHandler(int sinal);

/* OBSERVACOES*/
/*
    Tanto sem signal quanto com, nao houve qualquer captura
    de sinal ou qualquer excecao sendo levantada. 
*/

int main(void)
{
    float f1, f2;

    signal(SIGFPE, fpeHandler); // Floating Point Exception

    printf("Informe os dois numeros reais: ");
    scanf("%f %f", &f1, &f2);

    printf("\n");
    printf("Soma:    %+.2f\n", f1 + f2);
    printf("Subtr.:  %+.2f\n", f1 - f2);
    printf("Prod.:   %+.2f\n", f1 * f2);
    printf("Div.:    %+.2f\n", f1 / f2);

    return 0;
}

// Trata Floating Point Exception (FPE = 8)
void fpeHandler(int sinal)
{
    puts("\nExcecao de ponto flutuante detectada!");
    exit(EXIT_FAILURE);
}
