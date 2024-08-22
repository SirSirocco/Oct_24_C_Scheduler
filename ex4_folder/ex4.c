#include <unistd.h>     // fork, exec
#include <sys/wait.h>   // waitpid
#include <stdio.h>
#include <stdlib.h>     // exit e NULL

// Referencia https://users.pja.edu.pl/~jms/qnx/help/watcom/clibref/src/exec.html

int main(void)
{
    int status;
    const char* fileName = "echo";
    char *argv[6] = 
    {
        fileName,
        "voce consegue ouvir o ECHO?",
        "ECHO ECHO",
        "ECHO ECHO ECHO",
        "ECHO ECHO",
        "ECHO"
    };

    if (fork() != 0) // Pai
    {
        waitpid(-1, &status, 0);
        puts("fim do processo pai");
    }

    else // Filho
    {
        printf("processo filho antes do exec\n");
        // execv("alo_mundo.exe", argv);        // Exibe "alo mundo" na tela
        execv("echo", argv);                    // Replica as mensagens de argv na shell
    }

    return 0;
}

/*
## Resposta ao exercicio

O comando execv sobrescreve a area da RAM com o codigo herdado pelo filho, pondo no lugar o codigo do programa cujo caminho
foi passado como primeiro argumento (no caso, "echo.exe"). Em seguida, argv corresponde a lista de argumentos que serao passados ao
programa, a semelhanca de quando se escrevem os argumentos em uma console. O caso do programa alo_mundo.exe eh inteiramente analogo.
*/