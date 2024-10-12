#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_EL 4

int main(void)
{
    int val = 0;

    puts("### Queue does not exist");
    Queue* queue = NULL;
    print_queue(queue);
    dequeue(queue);

    puts("\n### Create queue");
    queue = enqueue(5, NULL);
    print_queue(queue);

    puts("\n### Remove element");
    val = dequeue(queue);
    printf("%d\n", val);

    puts("\n## Empty queue");
    dequeue(queue);

    printf("Should be empty < ");
    print_queue(queue);
    printf(" >\n");

    puts("\n### More than two elments");
    for (int i = 0; i < NUM_EL; i++)
        queue = enqueue(i + 1, queue);

    print_queue(queue);
    for (int i = 0; i < NUM_EL; i++)
    {
        printf("%d\n", dequeue(queue));
        print_queue(queue);
    }
    print_queue(queue);

    free(queue);

    return 0;
}
