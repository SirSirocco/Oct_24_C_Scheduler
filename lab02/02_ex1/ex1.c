#include <stdio.h>      // perror
#include <stdlib.h>
#include <sys/ipc.h>    // Inter-Processs Communication
#include <sys/shm.h>    // Funcoes com prefixo "shm" (Shared Memory)
#include <sys/stat.h>   // Flags com sufixo USR
#include <sys/wait.h>   // waitpid
#include <unistd.h>     // fork

void exibeMatriz(int* matriz, int lin, int col);

int main(int argc, char* argv[])
{
    int status, pid, segmento[3], *matriz[3];
    int matAux1[9] = {5, 7, 9, 6, 3, 6, 3, 1, 2};
    int matAux2[9] = {5, 3, 0, 6, 2, 6, 5, 7, 0};
    int matAux3[9] = {0}; // Matriz resultante inicializada com 0
    int* matAux[3] = {matAux1, matAux2, matAux3};
    int tamSeg = sizeof(segmento) / sizeof(segmento[0]);

    // Alocacao de memoria compartilhada
    for (int i = 0; i < tamSeg; i++)
    {
        segmento[i] = shmget(IPC_PRIVATE, 9 * sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
        matriz[i] = (int*)shmat(segmento[i], NULL, 0);
    }

    // Preenchimento de valores usando aritmetica de ponteiros
    for (int i = 0; i < tamSeg; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            *(matriz[i] + j) = *(matAux[i] + j);
        }
        printf("Matriz %d criada:\n", i + 1);
        exibeMatriz(matriz[i], 3, 3);
        printf("\n");
    }

    // Processamento para cada linha da matriz
    for (int i = 0; i < tamSeg; i++)
    {
        if ((pid = fork()) < 0) // Erro
        {
            perror("fork");
            exit(-4);
        }
        else if (pid == 0) // Processo filho
        {
            for (int j = 0; j < 3; j++)
            {
                *(matriz[2] + 3 * i + j) = *(matriz[0] + 3 * i + j) + *(matriz[1] + 3 * i + j);
            }
            exit(EXIT_SUCCESS);
        }
        else // Processo pai
        {
            printf("Linha %d preenchida:\n", i + 1);
            waitpid(pid, &status, 0);
            exibeMatriz(matriz[2], 3, 3);
            printf("\n");
        }
    }

    // Desanexar e remover segmentos de memoria compartilhada
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

/*
## Resposta ao exercicio

Inicialmente, foram alocadas tres matrizes 3 x 3 linearizadas (vetores 1 x 9) na area de memoria compartilhada
por meio do comando "shmget", que retornou, para cada chamada, um identificador de segmento. A partir dos
identificadores, com o uso de "shmat", os enderecos iniciais das matrizes foram atribuidos aos ponteiros armazendos
em "matriz". Em seguida, cada matriz foi preenchida com auxilio de "matAux", sendo ao final exibida. Logo apos,
para cada linha da matriz solucao (a terceira), foi criado, por meio do "fork()", um processo filho responsavel por
atualizar as entradas da linha atual com a soma das entradas respectivas das outras duas matrizes. Em todos os casos,
o processo pai esperou seu filho terminar para, enfim, exibir o estado da matriz solucao. O pai, entao, desatribuiu
os ponteiros para memoria compartilhada com "shmdt" e removeu tais segmentos com "shmctl" ao passar a flag IPC_RMID.
Por fim, foi encerrado com "return 0".

Cabe mencionar que, quando se manipularam as matrizes na regiao compartilhada, os processos funcionaram corretamente
com o uso de aritmetica de ponteiros em detrimento de indexacao. O porque disso ainda nao nos eh sabido e, provavelmente,
envolve questoes de hardware mais minuciosas.
*/