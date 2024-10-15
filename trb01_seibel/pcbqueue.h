#pragma once

#include <sys/wait.h>

#define NUM_ARGS 2

struct pcb
{
    pid_t pid;
    int pc;
    const char* syscallargs[NUM_ARGS];
};

typedef struct pcb PCB;
typedef PCB* hotspot;
typedef struct queue Queue;

PCB* new_pcb(pid_t pid, int pc, const char* arg0, const char* arg1);
void free_pcb(PCB* pcb);
Queue* enqueue(hotspot val, Queue* queue);
hotspot dequeue(Queue* queue);
void free_queue(Queue* queue);
void print_queue(Queue* queue);
