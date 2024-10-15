#include "mysignal.h"
#include "pcbqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

#define TRUE 1
#define INT_CTL_PATH    "./inter_control"
#define PATH            "./a"
#define NUM_PRCS        1       // Number of processes
#define ARGC            5
#define SYSC_ARGC       2
#define OFFSET_C        3       // Number of elements in offset vector   
#define PAGE            4096    // byte(s)
#define BUF_SIZE        64      // byte(s)

static void error(const char* msg);
void timeslice_handler(int signal);
void iointerrupt_handler(int signal);
void syscall_handler(int signal);
PCB* new_process(const char* path, char** argv);
PCB* init(int p_count, const char* path, char** argv);

int shm_offset_v[ARGC] = { 0, 100, 200 },
    *pc;

char shmidbuf[BUF_SIZE];
     *argv[ARGC] = { shmidbuf, "0", "100", "200", NULL },
     **syscallarg[SYSC_ARGC];

void *shmptrbase; // Base of shared memory

PCB *current_pcb;       // Process Control Board of the current process
    *inter_control_pcb; // PCB of Interrupt controller

Queue *ready, // Processes in ready state
      *wait;  // Processes in wait  state

int main(void)
{
    int shmid;

    signal(SIGIRQ1, timeslice_handler);
    signal(SIGIRQ2, iointerrupt_handler);
    signal(SIGSYS, syscall_handler);

    if ((shmid = shmget(IPC_CREAT, PAGE, S_IRWXU)) == -1)
        error("shmid");
    
    if ((shmptrbase = shmat(shmid, NULL, 0)) == (void*)-1)
        error("shmat");

    sprintf(shmidbuf, "%d", shmid); // Saves shmid in string form to send it to child processes via argv

    // Mapping shared memory for Inter-process communication (IPC)
    pc = (int*)(shmptrbase + shm_offset_v[0]);
    
    for (int i = 0; i < SYSC_ARGC; i++)
        syscallarg[i] = (char**)(shmptrbase + shm_offset_v[i + 1]);

    // Allocate queues
    ready = enqueue(NULL, NULL);
    wait = enqueue(NULL, NULL);

    // Interrupt Controller
    inter_control_pcb = new_process(INT_CTL_PATH, NULL);

    // Processes to be scheduled
    current_pcb = init(PATH, NUM_PRCS, argv);
    kill(current_pcb->pid, SIGCONT);

    // Scheduling
    while (TRUE);
}

// Prints error message and exits with EXIT_FAILURE.
static void error(const char* msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

PCB* new_process(const char* path, char** argv)
{
    pid_t pid;

    if ((pid = fork()) < 0) // Error
        error("fork");

    else if (pid == 0) // Child
        execv(path, argv);

    return new_pcb(pid, 0, NULL, NULL);
}

PCB* init(int p_count, const char* path, char** argv)
{
    PCB* first = new_process(path, argv);
    kill(first->pid, SIGSTOP);

    for (int i = 1; i < p_count; i++)
    {
        enqueue(new_process(path, argv), ready);
        kill(first->pid, SIGSTOP);
    }

    return first;
}

void context_swap(void)
{
    if (current_pcb)
    {
        kill(SIGSTOP, current_pcb->pid);
        current_pcb->pc = *pc;
        current_pc->syscallarg
    }

    enqueue(current_pcb, ready);
    current_pcb = dequeue(ready);

    if (current_pcb)
    {
        kill(SIGCONT, current_pcb->pid);
        *pc = current_pcb->pc;
    }
}

// Handles end of time_slice.
// Swaps the context to next ready process.
void timeslice_handler(int signal)
{
    context_swap();
}

// Handles a syscall.
// Swaps the context to next ready process.
void syscall_handler(int signal)
{
   context_swap(); 
}

// Dequeues from wait and enqueues in ready.
// Handles finishing of an IO operation.
void iointerrupt_handler(int signal)
{
    enqueue(dequeue(wait), ready);
}
