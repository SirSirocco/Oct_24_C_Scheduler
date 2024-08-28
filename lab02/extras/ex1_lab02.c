#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h> // fork
#include <sys/wait.h>
#include <stdio.h> // puts
#include <stdlib.h>

void exibeMatriz(int* matriz, int lin, int col);

int main (int argc, char *argv[])
{
    int status, pid, segmento[3], * matriz[3];
    int mat1[9] =
    { 
        5, 7, 9, 
        6, 3, 6, 
        3, 1, 2
    },

    mat2[9] =
    {
        5, 3, 0,
        6, 2, 6,
        5, 7, 0
    },

    mat3[9] =
    {
        0
    };

    int* mats[3] = {mat1, mat2, mat3};

    int tamSeg = sizeof(segmento) / sizeof(segmento[0]);
        tamMats = sizeof(mats) / sizeof(mats[0]);

    // Alocacao de memoria
    for (int i = 0; i < tamSeg i++)
    {
        segmento[i] = shmget(IPC_PRIVATE, 9 * sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
        matriz[i] = (int*)shmat(segmento[i], 0, 0);
    }

    // Preenchimento de valores
    for (int i = 0; i < tamMats; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            matriz[i][j] = mats[i][j];
            printf("%d\n", matriz[i][j]);
        }

        exibeMatriz(matriz[i], 3, 3);
        printf("\n");
    }

    for (int k = 0; k < 3; k++) // Para cada linha
    {
        if ((pid = fork()) < 0) // Erro
            {
                puts("Ocorreu um erro na criacao do processo");
                exit(-4);
            }
            
            else if (pid == 0) // Filho
            {
                for (int i = 0; i < 3; i++)
                {
                    matriz[2][3 * k + i] = matriz[0][3 * k + i] + matriz[1][3 * k + i];
                    exit(-k);
                }
            }

            else // Pai
            {
                waitpid(pid, 0, 0);
                exibeMatriz(matriz[2], 3, 3);
                printf("\n");
            }
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
            printf(" %3d", matriz[lin * i + j]);
        }
        printf("   |\n");
    }
}