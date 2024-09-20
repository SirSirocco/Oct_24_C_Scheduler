#include <stdio.h>
#include <unistd.h>

#define TRUE 1
#define TEMPO 5 // Em segundos

int main(void)
{
    pid_t pid = getpid();

    while (TRUE)
    {
        printf("PID %d\n", pid);
        sleep(TEMPO);
    }
}