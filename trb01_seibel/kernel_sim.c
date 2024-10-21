#include "mysignal.h"
#include "pcbqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

#define TRUE 1
#define INT_CTL_PATH    "./inter_control"
#define PATH            "./a"
#define NUM_PRCS        3       // Number of processes
#define ARGC            6
#define SYSC_ARGC       2
#define OFFSET_C        4       // Number of elements in offset vector   
#define PAGE            4096    // byte(s)
#define BUF_SIZE        64      // byte(s)

static void error(const char* msg);
void timeslice_handler(int signal);
void iointerrupt_handler(int signal);
void syscall_handler(int signal);
PCB* new_process(const char* path, char** argv);
PCB* init(int p_count, const char* path, char** argv);

int shm_offset_v[ARGC] = { 0, 100, 200, 300 },
    *pc;

char shmidbuf[BUF_SIZE],
     *argv[ARGC] = { shmidbuf, "0", "100", "200", "300", NULL },
     *syscallarg[SYSC_ARGC];

void *shmptrbase; // Base of shared memory

PCB *current_pcb,       // Process Control Board of the current process
    *inter_control_pcb; // PCB of Interrupt controller

Queue *ready_q, // Processes in ready state
      *wait_q;  // Processes in wait  state

int main(void)
{
    int shmid;

    signal(SIGIRQ1, timeslice_handler);
    signal(SIGIRQ2, iointerrupt_handler);
    signal(SIGSYS, syscall_handler);

    if ((shmid = shmget(IPC_PRIVATE, PAGE, IPC_CREAT | S_IRWXU)) == -1)
        error("shmid");
    
    if ((shmptrbase = shmat(shmid, NULL, 0)) == (void*)-1)
        error("shmat");

    sprintf(shmidbuf, "%d", shmid); // Saves shmid in string form to send it to child processes via argv

    // Mapping shared memory for Inter-process communication (IPC)
    pc = (int*)(shmptrbase + shm_offset_v[0]);
    
    for (int i = 0; i < SYSC_ARGC; i++)
        syscallarg[i] = (char*)(shmptrbase + shm_offset_v[i + 1]);

    // Allocate queues
    ready_q = new_queue();
    wait_q = new_queue();

    // Interrupt Controller
    inter_control_pcb = new_process(INT_CTL_PATH, NULL);

    // Processes to be scheduled
    current_pcb = init(NUM_PRCS, PATH, argv);
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
    puts("init");
    PCB* first, *current;
    first = new_process(path, argv);
    kill(first->pid, SIGSTOP);
    printf("PID %d\n", first->pid);

    for (int i = 1; i < p_count; i++)
    {
        enqueue((current = new_process(path, argv)), ready_q);
        kill(current->pid, SIGSTOP);
        printf("PID %d\n", current->pid);
    }

    return first;
}

void context_save(Queue* enq)
{
    if (!current_pcb)
        return;
    
    kill(current_pcb->pid, SIGSTOP);
    printf("PID %d stopped\n", current_pcb->pid);
    current_pcb->pc = *pc;
    // for (int i = 0; i < SYSC_ARGC; i++)
    //     strcpy(current_pcb->syscallarg[i], syscallarg[i]);
    enqueue(current_pcb, enq);
}

void context_swap(Queue* deq)
{
    int status;
    current_pcb = dequeue(deq);

    if (current_pcb)
    {
        if (current_pcb->pid == waitpid(current_pcb->pid, &status, WNOHANG))
        {
            printf("PID %d has finished\n", current_pcb->pid);
            free_pcb(current_pcb);
            current_pcb = NULL;
            return;
        }
        *pc = current_pcb->pc;
        // *status = current_pcb->status;
        printf("%d \n", *pc);
        kill(current_pcb->pid, SIGCONT);
        // for (int i = 0; i < SYSC_ARGC; i++)
        //     syscallarg[i] = current_pcb->syscallarg[i];
        printf("PID %d continued\n", current_pcb->pid);
    }
    else
        puts("idle");
}

// Handles end of time_slice.
// Swaps the context to next ready process.
void timeslice_handler(int signal)
{
    kill(inter_control_pcb->pid, SIGSTOP);
    context_save(ready_q);
    context_swap(ready_q);
    kill(inter_control_pcb->pid, SIGCONT);
    // puts("ts");
}

// Handles a syscall.
// Swaps the context to next ready process.
void syscall_handler(int signal)
{
    kill(inter_control_pcb->pid, SIGSTOP);
    strcpy(current_pcb->syscallarg[0], syscallarg[0]);
    strcpy(current_pcb->syscallarg[1], syscallarg[1]);
    context_save(wait_q);
    printf("PID %d requests systemcall(%s, %s)\n", current_pcb->pid, current_pcb->syscallarg[0], current_pcb->syscallarg[1]);
    context_swap(ready_q);
    kill(inter_control_pcb->pid, SIGCONT);
    kill(inter_control_pcb->pid, SIGIRQ2);
}

// Dequeues from wait and enqueues in ready.
// Handles finishing of an IO operation.
void iointerrupt_handler(int signal)
{
    PCB* pcb;
    kill(inter_control_pcb->pid, SIGSTOP);
    // dequeue(wait_q);
    pcb = dequeue(wait_q);
    printf("%d\n", pcb->pid);
    printf("PID %d's systemcall(%s, %s) finished\n", pcb->pid, pcb->syscallarg[0], pcb->syscallarg[1]);
    enqueue(pcb, ready_q);
    kill(inter_control_pcb->pid, SIGCONT);
}

