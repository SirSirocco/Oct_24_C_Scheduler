#pragma once

#include <sys/wait.h>

#define NUM_ARGS 2

struct pcb
{
    pid_t pid;
    int pc;
    char* syscallarg[NUM_ARGS];
};

typedef struct pcb PCB;
typedef PCB* hotspot;
typedef struct queue Queue;

PCB* new_pcb(pid_t pid, int pc, char* arg0, char* arg1);
void free_pcb(PCB* pcb);
Queue* enqueue(hotspot val, Queue* queue);
hotspot dequeue(Queue* queue);
void free_queue(Queue* queue);
