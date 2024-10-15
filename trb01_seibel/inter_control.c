#include "mysignal.h"
#include <stdio.h>
#include <sys/wait.h>   // pid_t, getppid
#include <unistd.h>     // sleep

#define TRUE 1
#define TIME_SLICE  1   // second(s)
#define IO_TIME     3   // second(s)

void syscall_handler(int signal);
void alarm_handler(int signal);

int io_count = 0;   // Counts number of requested IO syscalls in progress
pid_t parent;       // Scheduler (kernel)

int main(void)
{
    parent = getppid(); // Get parent process's PID

    signal(SIGIRQ2, syscall_handler);
    signal(SIGALRM, alarm_handler);

    while (TRUE)
    {
        sleep(TIME_SLICE);
        kill(parent, SIGIRQ1); // Signals end of time-slice to parent
    }
}

// Simulates IO operation.
// If this is the only syscall, sets alarm.
void syscall_handler(int signal)
{
    if (!io_count)
        alarm(IO_TIME);
    io_count++;
}

// Generates interrupt and signals it to father process.
// Sets alarm to signal end of next IO operation if it exists.
void alarm_handler(int signal)
{
    io_count--;             // IO finished
    kill(parent, SIGIRQ2);  // Parent signaled of IO end 
    if (io_count > 0)       // If still more IOs
        alarm(IO_TIME);     // Sets next alarm
}
