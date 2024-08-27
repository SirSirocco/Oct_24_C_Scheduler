#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h> // fork
#include <sys/wait.h>
#include <stdio.h> // puts
#include <stdlib.h>

void exibeMatriz(int* matriz, int lin, int col);

int main(int argc, char *argv[])
{
    int status, pid, segmento[3], *matriz[3];
    int mat1[9] = {5, 7, 9, 6, 3, 6, 3, 1, 2};
    int mat2[9] = {5, 3, 0, 6, 2, 6, 5, 7, 0};
    int mat3[9] = {0}; // Matriz resultante inicializada com 0

    int* mats[3] = {mat1, mat2, mat3};

    int tamSeg = sizeof(segmento) / sizeof(segmento[0]);

    // Alocacao de memoria compartilhada
    for (int i = 0; i < tamSeg; i++)
    {
        segmento[i] = shmget(IPC_PRIVATE, 9 * sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
        matriz[i] = (int*)shmat(segmento[i], 0, 0);
    }

    // Preenchimento de valores usando aritmética de ponteiros
    for (int i = 0; i < tamSeg; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            *(matriz[i] + j) = *(mats[i] + j);
        }
        exibeMatriz(matriz[i], 3, 3);
        printf("\n");
    }

    // Processamento: para cada linha da matriz
    for (int k = 0; k < 3; k++)
    {
        if ((pid = fork()) < 0) // Erro
        {
            puts("Ocorreu um erro na criacao do processo");
            exit(-4);
        }
        else if (pid == 0) // Processo filho
        {
            for (int i = 0; i < 3; i++)
            {
                *(matriz[2] + 3 * k + i) = *(matriz[0] + 3 * k + i) + *(matriz[1] + 3 * k + i);
            }
            exit(0);
        }
        else // Processo pai
        {
            waitpid(pid, &status, 0);
            exibeMatriz(matriz[2], 3, 3);
            printf("\n");
        }
    }

    // Desanexar e remover segmentos de memória compartilhada
    for (int i = 0; i < tamSeg; i++)
    {
        shmdt(matriz[i]);
        shmctl(segmento[i], IPC_RMID, 0);
    }

    return 0;
}

void exibeMatriz(int* matriz, int lin, int col)
{
    for (int i = 0; i < lin; i++)
    {
        printf("|");
        for (int j = 0; j < col; j++)
        {
            printf(" %3d", *(matriz + i * col + j));
        }
        printf("   |\n");
    }
}