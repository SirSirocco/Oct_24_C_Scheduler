#include "mysem.h"
#include "mysignal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define SYSC_ARGC   2   // Number of system call arguments
#define OFFSET_C    3   // Number of elements in offset vector  
#define MAX_ITER    10  // Number of iterations
#define R_ITER      3   // Iteration in which read syscall is requested
#define W_ITER      6   // Iteration in which write syscall is requested
#define ITER_T      1   // Time of iteration (in seconds)

/* PROTOTYPES */
static void error(const char* msg);
void systemcall(char* stream, char* mode);
void cont_handler(int signal);

/* GLOBAL VARIABLES */
int semid;
int mutex_syscall;
int shm_offset_v[OFFSET_C]; // Shared memory offsets in bytes with respect to shmptrbase (0 -> pc, 1 -> syscall_arg0, 2 -> syscall_arg1).
int* pc; // Program Counter: counts iterations.

pid_t parent; // Scheduler (kernel).

void* shmptrbase; // Base of shared memory.

char* syscallarg[SYSC_ARGC]; // System call arguments.

/* FUNCTIONS */
int main(int argc, char** argv)
{
    int shmid;
    semid = atoi(argv[0]);
    shmid = atoi(argv[1]);

    // Setting handlers
    signal(SIGCONT, cont_handler);

    parent = getppid(); // Get parent process's PID

    // Setting semaphore
    if ((mutex_syscall = semget(semid, 1, IPC_CREAT | S_IRWXU)) == -1)
        error("semget");

    // Setting shared memory
    if ((shmptrbase = shmat(shmid, NULL, 0)) == (void*)-1) // Attach to shared memory
        error("shmat");

    for (int i = 0; i < OFFSET_C; i++) // Get offsets defined by scheduler
        shm_offset_v[i] = atoi(argv[i + 2]);

    // Mapping shared memory for Inter-process communication (IPC)
    pc = (int*)(shmptrbase + shm_offset_v[0]);
    
    for (int i = 0; i < SYSC_ARGC; i++)
        syscallarg[i] = (char*)(shmptrbase + shm_offset_v[i + 1]);

    // Iterations
    while (*pc < MAX_ITER)
    {
        if (*pc == R_ITER)
            systemcall("D1", "R");
        
        if (*pc == W_ITER)
            systemcall("D1", "W");

        sleep(ITER_T);

        sem_down(mutex_syscall, 0);
        (*pc)++;
        sem_up(mutex_syscall, 0);
    }

    shmdt(shmptrbase); // Detaches from shared memory (does not remove shm)
    exit(EXIT_SUCCESS);
}

// Prints error message and exits with EXIT_FAILURE.
static void error(const char* msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

// Simulates system call.
// Stream will always be "D1" (device 1).
// Mode can be "R" (read) or "W" (write).
void systemcall(char* stream, char* mode)
{
    sem_down(mutex_syscall, 0);
    /* ATOMIC */
    strcpy(syscallarg[0], stream);
    strcpy(syscallarg[1], mode);
    /* ATOMIC */
    sem_up(mutex_syscall, 0);

    kill(parent, SIGSYS); // Warns scheduler of syscall 

    pause(); // Waits for parent to signal with SIGCONT
}

// Necessary to make pause() in systemcall work adequately.
void cont_handler(int signal)
{
}
