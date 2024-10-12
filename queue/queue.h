typedef struct queue Queue;
typedef struct node Node;
typedef int hotspot;

Queue* enqueue(hotspot val, Queue* queue);
hotspot dequeue(Queue* queue);
void free_queue(Queue* queue);
void print_queue(Queue* queue);
