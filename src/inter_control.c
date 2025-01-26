#include "mysem.h"
#include "mysignal.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>   // pid_t, getppid
#include <unistd.h>     // sleep

#define TRUE 1
#define TIME_SLICE  1   // second(s)
#define IO_TIME     3   // second(s)

static void error(const char* msg);
void syscall_handler(int signal);
void alarm_handler(int signal);

int mutex;
int io_count = 0;   // Counts number of requested IO syscalls in progress
pid_t parent;       // Scheduler (kernel)

int main(int argc, char** argv)
{
    int semid = atoi(argv[0]);
    parent = getppid(); // Get parent process's PID

    // Setting semaphore
    if ((mutex = semget(semid, 1, IPC_CREAT | S_IRWXU)) == -1)
        error("semget");

    signal(SIGIRQ1, syscall_handler);
    signal(SIGALRM, alarm_handler);

    while (TRUE)
    {
        sleep(TIME_SLICE);
        sem_down(mutex, 1);
        kill(parent, SIGIRQ0); // Signals end of time-slice to parent
        sem_up(mutex, 1);
    }
}

// Prints error message and exits with EXIT_FAILURE.
static void error(const char* msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
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
    kill(parent, SIGIRQ1);  // Parent signaled of IO end 
    if (io_count > 0)       // If still more IOs
        alarm(IO_TIME);     // Sets next alarm
}
