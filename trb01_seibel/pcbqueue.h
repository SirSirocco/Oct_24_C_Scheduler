#pragma once

#include <sys/wait.h>   // pid_t

#define SYSC_ARGS 2     // Number of system call arguments
#define BUFF_SIZE 64    // Buffer size

struct pcb // Process Control Board
{
    pid_t pid;                              // Process ID
    int pc;                                 // Program counter
    char syscallarg[SYSC_ARGS][BUFF_SIZE];  // System call arguments
};

typedef struct pcb PCB;
typedef PCB* hotspot;
typedef struct queue Queue;

PCB*    new_pcb(pid_t pid, int pc, char* arg0, char* arg1);
void    print_pcb(PCB* pcb);
void    free_pcb(PCB* pcb);
Queue*  new_queue(void);
Queue*  enqueue(PCB* val, Queue* queue);
PCB*    dequeue(Queue* queue);
void    free_queue(Queue* queue);
