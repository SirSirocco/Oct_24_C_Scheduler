/* Pedro de Almeida Barizon 2211350 */

/* DEPENDENCIAS EXTERNAS */
#include <stdio.h>      // printf
#include <stdlib.h>     // exits
#include <sys/wait.h>   // waitpid
#include <unistd.h>     // fork

/* DEFINICOES */
#define TAM 10          // Tamanho do vetor manipulado nos processos

void exibe_vetor(int n, int* v);
void exibe_vetor_ln(int n, int* v);

int main(void)
{
    int v[TAM] = { 0 }, pid, status;

    if ((pid = fork()) < 0) // Erro
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) // Filho
    {
        for (int i = 0; i < TAM; i++)
            v[i]--;
        printf("vetor exibido pelo filho: ");
        exibe_vetor_ln(TAM, v);
        exit(EXIT_SUCCESS);
    }
    else // Pai
    {
        for (int i = 0; i < TAM; i++)
            v[i]++;
        printf("vetor exibido pelo pai: ");
        exibe_vetor_ln(TAM, v);
        waitpid(pid, &status, 0); // Espera filho terminar
    }

    return 0;
}

/* FUNCOES AUXILIARES */
void exibe_vetor(int n, int* v)
{
    FILE* file = stdout;

    fprintf(file, "{ %d", v[0]);

    for (int i = 1; i < n; i++)
        fprintf(file, ", %d", v[i]);

    fprintf(file, " }");
}

// Adiciona '\n' apos exibicao do vetor
void exibe_vetor_ln(int n, int* v)
{
    exibe_vetor(n, v);
    printf("\n");
}
