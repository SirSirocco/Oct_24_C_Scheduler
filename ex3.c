#include <unistd.h>     // exec
#include <sys/wait.h>   // waitpid
#include <stdio.h>
#include <stdlib.h>     // exit e NULL

void exibeVetor(int* v, int n);
void ordenaVetor(int* v, int n);

int main(void)
{
    int v[10], tam = sizeof(v) / sizeof(v[0]), status;

    for (int i = 0; i < tam; i++)
        fscanf(stdin, " %d", v + i);

    exibeVetor(v, tam);
    printf("\n");

    if (fork() != 0) // Pai
    {
        waitpid(-1, &status, 0);
        exibeVetor(v, tam);
        printf("\n");
    }

    else // Filho
    {
        ordenaVetor(v, n);
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}

void exibeVetor(int* v, int n)
{
    FILE* file = stdout;

    fprintf(file, "{ %d", v[0]);

    for (int i = 1; i < n - 1; i++)
        fprintf(file, ", %d", v[i]);

    fprintf(file, " }", v[n - 1]);
}

void ordenaVetor(int* v, int n)
{
    int menor, aux;

    for (int i = 0; i < n; i++)
    {
        menor = i;

        for (int j = i + 1; j < n; j++)
        {
            if (v[j] < v[menor])
                menor = j;
        }

        aux = v[i];
        v[i] = v[menor];
        v[menor] = aux;
    }
}

/*
## Resposta ao exercicio

    Foram exibidos dois vetores iguais, pois a ordenacao feita pelo filho nao surtiu efeito no pai,
    uma vez que, como visto no exercicio anterior, os processos lidaram com areas de memoria distintas
    e, portanto, vetores diferentes.
*/