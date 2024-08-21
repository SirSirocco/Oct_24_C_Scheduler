#include <unistd.h>     // fork, exec
#include <sys/wait.h>   // waitpid
#include <stdio.h>
#include <stdlib.h>     // exit e NULL

void exibeVetor(int* v, int n);
void exibeVetorLn(int* v, int n);
void ordenaVetor(int* v, int n);

int main(void)
{
    int v[10], tam = sizeof(v) / sizeof(v[0]), status;

    printf("digite 10 valores inteiros:\n");

    for (int i = 0; i < tam; i++)
        fscanf(stdin, " %d", v + i);
    
    printf("antes do fork:\n");
    exibeVetorLn(v, tam);

    if (fork() != 0) // Pai
    {
        waitpid(-1, &status, 0);
        printf("depois do fork:\n");
        exibeVetorLn(v, tam);
    }

    else // Filho
    {
        ordenaVetor(v, tam);
        printf("vetor ordenado pelo filho:\n");
        exibeVetorLn(v, tam);
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}

void exibeVetorLn(int* v, int n)
{
    exibeVetor(v, n);
    printf("\n");
}


void exibeVetor(int* v, int n)
{
    FILE* file = stdout;

    fprintf(file, "{ %d", v[0]);

    for (int i = 1; i < n; i++)
        fprintf(file, ", %d", v[i]);

    fprintf(file, " }");
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