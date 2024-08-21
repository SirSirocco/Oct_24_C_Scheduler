#include <unistd.h>     // fork, exec
#include <sys/wait.h>   // waitpid
#include <stdio.h>
#include <stdlib.h>     // exit e NULL

int main(void)
{
    int status, var;
    /*
    int* var = (int*)malloc(sizeof(int)); NUNCA MAIS FAZER (wild pointer)

    if (!var)
        exit(EXIT_FAILURE); // Impossivel alocar memoria
    */

    if (fork() != 0) // Pai
    {
        var = 1;
        printf("valor de var no pai antes do filho: %d\n", var);

        waitpid(-1, &status, 0);

        printf("valor de var no pai depois do filho: %d\n", var);
        // free(var);
    }

    else // Filho
    {
        var = 5;
        printf("valor de var no filho: %d\n", var);
        exit(EXIT_SUCCESS);
    }

    return 0;
}

/*
## Resposta ao exercicio

    O valor de var nao foi o mesmo nos dois programas, mesmo depois do retorno do filho ao pai.
    Isso se explica pelo fato de que os codigos e as variaveis dos programas respectivos aos processos foram 
    armazenados em areas diferentes na RAM. Dessa forma, nao houve compartilhamento de variaveis, ainda
    que estas pudessem ter sido alocadas dinamicamente.
*/