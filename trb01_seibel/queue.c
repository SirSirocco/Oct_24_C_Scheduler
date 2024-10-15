#include "queue.h"
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

// Creates new node, but does not initialize it.
// In case of memory failure, terminates the program.
static struct node* create_node(void)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));

    if (!node)
    {
        perror("malloc_node");
        exit(EXIT_FAILURE);
    }

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
        {
            perror("malloc_queue");
            exit(EXIT_FAILURE);
        }
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

// Prints every node of queue.
void print_queue(struct queue* queue)
{
    struct node* aux;
    
    if (!queue) // If queue does not exist, prints nothing
        return;
    
    aux = queue->first;

    while (aux)
    {
        printf("Addrs: %p\nVal: %-4d\nNext: %p\n\n", aux, aux->val, aux->next);
        aux = aux->next;
    }
}
