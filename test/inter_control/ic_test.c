#include "mysignal.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define TRUE 1
#define TIME 2
#define INT_CTL_PATH "./inter_control"

void timeSliceHandler(int signal);
void ioInterruptHandler(int signal);
void alarmHandler(int signal);

pid_t interControl;

int main(void)
{
    signal(SIGIRQ1, timeSliceHandler);
    signal(SIGIRQ2, ioInterruptHandler);
    signal(SIGALRM, alarmHandler);

    alarm(TIME);

    if ((interControl = fork()) < 0) // Error
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (interControl == 0) // Child
    {
        execv(INT_CTL_PATH, NULL);
    }

    // Parent
    while (TRUE)
    {
    }   
}

void timeSliceHandler(int signal)
{
    printf("1 segundo...\n");
}

void ioInterruptHandler(int signal)
{
    printf("Interrupcao IO...\n");
}

void alarmHandler(int signal)
{
    kill(interControl, SIGIRQ2);
    alarm(TIME);
}
