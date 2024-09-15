#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define EVER ;;

int main(void)
{
    pid_t pid = getpid();

    for (EVER)
    {
        printf("PID %d\n", pid);
        usleep(500000); // Dorme por 500 ms
    }
}
