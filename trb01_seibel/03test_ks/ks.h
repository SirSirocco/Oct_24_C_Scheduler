#include "mysignal.h"
#include "pcbqueue.h"

void timeslice_handler(int signal);
void iointerrupt_handler(int signal);
void syscall_handler(int signal);
PCB* new_process(const char* path, char** argv);
PCB* init(int p_count, const char* path, char** argv);
void context_swap(Queue* enq, Queue* deq);
