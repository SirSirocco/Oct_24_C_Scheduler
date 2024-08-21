#include <unistd.h>     // fork, exec
#include <sys/wait.h>   // waitpid
#include <stdio.h>
#include <stdlib.h>     // exit e NULL

int main(void) 
{
    int pid, status;

    pid = getpid();
    printf("pid do pai: %d\n", pid);

    if (fork() != 0) // Pai
    {
        waitpid(-1, &status, 0);
    }

    else // Filho
    {
        pid = getpid();
        printf("pid do filho: %d\n", pid);
        exit(EXIT_SUCCESS);
    }

    return 0;
}