#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "kernel_sim.h"



int main() 
{
    // Here the programa read the number of process its between 3 and 5.
    printf("Enter the number of application processes (between %d and %d): ", MIN_PROCESSES, MAX_PROCESSES);
    scanf("%d", &num_processes);
    if (num_processes < MIN_PROCESSES || num_processes > MAX_PROCESSES) 
    {
        printf("This number isn't valid...\n");
        return 1;
    }

    // Memory aloccation for the process and it's status.
    processes = malloc(num_processes * sizeof(pid_t));
    process_states = malloc(num_processes * sizeof(ProcessState));

    // Creating the Kernel
    kernel_pid = fork();
    if (kernel_pid == 0) 
    {
        Kernel_sim(); // Executing the Kernel.
    }

    // Creating InterController Sim
    controller_pid = fork();
    if (controller_pid == 0) 
    {
        Inter_controller_sim(); // Executing the InterController Sim
    }

    // Waiting the Kernel execution.
    waitpid(kernel_pid, NULL, 0);


    free(processes);
    free(process_states);
    return 0;
}

