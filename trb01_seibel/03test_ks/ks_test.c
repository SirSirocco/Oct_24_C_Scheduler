#include "ks.h"
#include "pcbqueue.h"
#include <stdio.h>
#include <unistd.h>

#define P_COUNT 5
#define TIME 3
#define PATH "./process"

extern Queue* ready_q, * wait_q;

int main(void)
{
    /* new_process: OK */
    // PCB* pcb = new_process(PATH, NULL);

    // print_pcb(pcb);

    // pcb->syscallarg[0] = "ARG0";
    // pcb->syscallarg[1] = "ARG1";

    // print_pcb(pcb);

    // free_pcb(pcb);

    /* init & context swap */
    ready_q = enqueue(NULL, NULL);
    wait_q = enqueue(NULL, NULL);
    PCB* pcb = init(P_COUNT, PATH, NULL);

    kill(pcb->pid, SIGCONT);

    while (1)
    {
        sleep(TIME);
        context_swap(ready_q, ready_q);
    }
}
