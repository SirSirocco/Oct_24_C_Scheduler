#include <stdio.h>

int main() {
    float num1, num2;
    
    printf("Digite o primeiro número: ");
    scanf("%f", &num1);
    
    printf("Digite o segundo número: ");
    scanf("%f", &num2);
    
    printf("Adição: %.2f + %.2f = %.2f\n", num1, num2, num1 + num2);
    printf("Subtração: %.2f - %.2f = %.2f\n", num1, num2, num1 - num2);
    printf("Multiplicação: %.2f * %.2f = %.2f\n", num1, num2, num1 * num2);
    
    if (num2 != 0) {
        printf("Divisão: %.2f / %.2f = %.2f\n", num1, num2, num1 / num2);
    } else {
        printf("Erro: Divisão por zero não permitida!\n");
    }
    
    return 0;
}