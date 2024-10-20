#include "pcbqueue.h"
#include <stdio.h>
#include <stdlib.h>

struct node
{
    hotspot val;
    struct node* next;
};

struct queue
{
    struct node* first;
    struct node* last;
};

// Prints error message and exits with EXIT_FAILURE.
static void error(const char* msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

// Creates new node, but does not initialize it.
// In case of memory failure, terminates the program.
static struct node* create_node(void)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));

    if (!node)
        error("malloc_node");

    return node;
}

// Adds element to end of queue.
// If queue is NULL, creates new queue.
struct queue* enqueue(hotspot val, struct queue* queue)
{
    if (!queue) // Creates queue
    {
        queue = (struct queue*)malloc(sizeof(struct queue));
        
        if (!queue)
            error("malloc_queue");
    }

    if (!queue->last) // Empty queue
        queue->first = queue->last = create_node();
    else // Non-empty queue
    {
        queue->last->next = create_node();

        // New node is now last
        queue->last = queue->last->next;
    }

    queue->last->val = val;
    queue->last->next = NULL;

    return queue;
}

// Removes first element of queue.
hotspot dequeue(struct queue* queue)
{
    struct node* aux;
    hotspot val;

    if (!queue)
    {
        fprintf(stderr, "\nError: Queue does not exist.\n");
        return NULL;
    }

    if (!queue->first)
    {
        fprintf(stderr, "\nWarning: Empty queue.\n");
        return NULL;
    }

    aux = queue->first;
    queue->first = queue->first->next;

    if (!queue->first) // Queue had only one element
        queue->last = NULL;

    val = aux->val;
    free(aux);

    return val;
}

// Frees all memory used by queue.
void free_queue(struct queue* queue)
{
    struct node* aux;

    aux = queue->first;

    while (aux)
    {
        queue->first = queue->first->next;
        free(aux);
        aux = queue->first;
    }

    free(queue);
}

// Creates pcb.
PCB* new_pcb(pid_t pid, int pc, char* arg0, char* arg1)
{
    PCB* pcb = (PCB*)malloc(sizeof(PCB));

    if (!pcb)
        error("malloc_pcb");

    pcb->pid = pid;
    pcb->pc = pc;
    pcb->syscallarg[0] = arg0;
    pcb->syscallarg[1] = arg1;

    return pcb;
}

void print_pcb(PCB* pcb)
{
    if (!pcb)
    {
        fprintf(stderr, "Empty PCB.\n");
        return;
    }

    printf("PID: %d\nPC: %d\nsyscallargs: %s, %s\n\n", pcb->pid, pcb->pc, pcb->syscallarg[0], pcb->syscallarg[1]);
}

// Liberates all memory of pcb.
void free_pcb(PCB* pcb)
{
    free(pcb);
}
