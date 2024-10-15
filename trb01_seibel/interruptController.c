#include "mysignal.h"
#include <stdio.h>
#include <sys/wait.h>   // pid_t, getppid
#include <unistd.h>     // sleep

#define TRUE 1
#define TIME_SLICE  1   // second(s)
#define IO_TIME     3   // second(s)

void syscallHandler(int signal);
void alarmHandler(int signal);

int ioCount = 0; // Counts number of requested IO syscalls in progress
pid_t parent;

int main(void)
{
    parent = getppid(); // Get parent process's PID

    signal(SIGIRQ2, syscallHandler);
    signal(SIGALRM, alarmHandler);

    while (TRUE)
    {
        sleep(TIME_SLICE);
        kill(parent, SIGIRQ1); // Signals end of time-slice to parent
    }
}

// Simulates IO operation.
// If this is the only syscall, sets alarm.
void syscallHandler(int signal)
{
    if (!ioCount)
        alarm(IO_TIME);
    ioCount++;
}

// Generates interrupt and signals it to father process.
// Sets alarm to signal end of next IO operation if it exists.
void alarmHandler(int signal)
{
    ioCount--;              // IO finished
    kill(parent, SIGIRQ2);  // Parent signaled of IO end 
    if (ioCount > 0)        // If still more IOs
        alarm(IO_TIME);     // Set next alarm
}
