#include "pcbqueue.h"
#include <stdio.h>

#define TAM 2

void print_pcb(PCB* pcb);

int main(void)
{
    Queue* q;
    PCB* pcb1, * pcb2;

    pcb1 = new_pcb(10, 100, "1000", "10000");
    pcb2 = new_pcb(20, 200, "2000", "20000");

    // Caso 1
    print_pcb(pcb1);

    // Caso 2
    q = enqueue(pcb1, NULL);
    enqueue(pcb2, q);

    for (int i = 0; i < TAM + 1; i++)
        print_pcb(dequeue(q));

    free_pcb(pcb1);
    free_pcb(pcb2);
    free_queue(q);

    return 0;
}

void print_pcb(PCB* pcb)
{
    if (!pcb)
    {
        fprintf(stderr, "PCB vazia\n");
        return;
    }

    printf("PID: %d\nPC: %d\nsyscallargs: %s, %s\n\n", pcb->pid, pcb->pc, pcb->syscallarg[0], pcb->syscallarg[1]);
}