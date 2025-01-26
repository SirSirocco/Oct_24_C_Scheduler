#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define TIME 3

int main(void)
{
    pid_t pid = getpid();
    // printf("Entrei PID %d\n", pid);
    while (1)
    {
        sleep(TIME);
        printf("%d\n", pid);
    }
}
