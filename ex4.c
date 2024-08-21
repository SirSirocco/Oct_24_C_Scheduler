#include <unistd.h>     // exec
#include <sys/wait.h>   // waitpid
#include <stdio.h>
#include <stdlib.h>     // exit e NULL

int main(void)
{
    int status;

    if (fork() != 0)
    {
        waitpid(-1, &status, 0);
        puts("processo pai executado");
    }

    else
    {
        execvp("ola_mundo.exe", NULL); // Exibe "ola mundo" na tela
    }

    return 0;
}