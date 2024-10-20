#include "mysignal.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define SYSC_ARGC   2
#define OFFSET_C    3       // Number of elements in offset vector  
#define MAX_ITER    10
#define R_ITER      3
#define W_ITER      6
#define ITER_T      2

static void error(const char* msg);
void systemcall(char* stream, char* mode);

int shm_offset_v[OFFSET_C], // Shared memory offsets in bytes with respect to shmptrbase (0 -> pc, 1 -> syscall_arg0, 2 -> syscall_arg1)
    *pc;                    // Program Counter

pid_t this, parent; // Scheduler (kernel)

void* shmptrbase; // Base of shared memory

char* syscallarg[SYSC_ARGC];

int main(int argc, char** argv)
{
    int shmid = atoi(argv[0]);

    // signal(SIGCONT, cont_handler);

    this = getpid();
    // printf("%d\n", this);
    parent = getppid(); // Get parent process's PID

    if ((shmptrbase = shmat(shmid, NULL, 0)) == (void*)-1) // Attach to shared memory
        error("shmat");

    for (int i = 0; i < OFFSET_C; i++) // Get offsets defined by scheduler
        shm_offset_v[i] = atoi(argv[i + 1]);

    // Mapping shared memory for Inter-process communication (IPC)
    pc = (int*)(shmptrbase + shm_offset_v[0]);
    
    for (int i = 0; i < SYSC_ARGC; i++)
        syscallarg[i] = (char*)(shmptrbase + shm_offset_v[i + 1]);

    for (; *pc < MAX_ITER; (*pc)++)
    {
        if (*pc == R_ITER)
        {
            // printf("%d\n", this);
            systemcall("D1", "R");
            // printf("PID %d: Finished systemcall(%s, %s)\n",  this, syscallarg[0], syscallarg[1]);
        }
        if (*pc == W_ITER)
        {
            // printf("%d\n", this);
            systemcall("D1", "W");
        }

        sleep(ITER_T);
    }

    shmdt(shmptrbase); // Detach from shared memory (does not remove shm)
    exit(this);
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
    strcpy(syscallarg[0], stream);
    strcpy(syscallarg[1], mode);
    kill(parent, SIGSYS);
    // pause();
    puts("oi");
}
