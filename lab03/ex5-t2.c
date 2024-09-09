#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void trata_SIGFPE(int sinal) {
    printf("Erro: Tentativa de divisão por zero capturada!\n");
    exit(1);
}

int main() {
    float num1, num2;
    
    signal(SIGFPE, trata_SIGFPE); // Captura o sinal SIGFPE

    printf("Digite o primeiro número: ");
    scanf("%f", &num1);
    
    printf("Digite o segundo número: ");
    scanf("%f", &num2);
    
    printf("Adição: %.2f + %.2f = %.2f\n", num1, num2, num1 + num2);
    printf("Subtração: %.2f - %.2f = %.2f\n", num1, num2, num1 - num2);
    printf("Multiplicação: %.2f * %.2f = %.2f\n", num1, num2, num1 * num2);

    // O manipulador de SIGFPE tratará o caso de divisão por zero
    printf("Divisão: %.2f / %.2f = %.2f\n", num1, num2, num1 / num2);
    
    return 0;
}