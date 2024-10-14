#include "kernel_sim.h"


pid_t kernel_pid, controller_pid;
pid_t *processes;
ProcessState *process_states;
int num_processes = 0;
int current_process = 0;


//The functions that start with 'handle' are used to manipulate signals, and the others are used to implement the Kernel.

void Handle_sigint(int sig) 
{
    printf("\nProcess status:\n");
    for (int i = 0; i < num_processes; i++)
     {
        printf("Process %d: PC = %d, status = %s, Acess D1: %d, Acess D2: %d\n", 
               process_states[i].ID, 
               process_states[i].program_counter,
               process_states[i].status == 0 ? "Executing" : (process_states[i].status == 1 ? "Blocked by D1" : "Blocked by D2"),
               process_states[i].acess_count_d1, 
               process_states[i].acess_count_d2);
    }
}




void Kernel_sim()
 {
    printf("Starting the  KernelSim...\n");

    // Setting the signal manipulation.
    signal(SIGALRM, Handle_irq0); // Time slice (IRQ0)
    signal(SIGUSR1, Handle_irq1); // Interruption D1 (IRQ1)
    signal(SIGUSR2, Handle_irq2); // Interruption D2 (IRQ2)
    signal(SIGINT, Handle_sigint); // Show process status.

    // Creating the aplication process.
    for (int i = 0; i < num_processes; i++) 
    {
        processes[i] = fork();
        if (processes[i] == 0)
         {
            Application_process(i + 1); // Executing the aplication process.
        } else 
        {
            // Initializes the process state.
            process_states[i].ID = i + 1;
            process_states[i].pid = processes[i];                               
            process_states[i].program_counter = 0;
            process_states[i].status = 0;
            process_states[i].running = 0;
            process_states[i].acess_count_d1= 0;
            process_states[i].acess_count_d2= 0;
            process_states[i].finished = 0;
        }
    }

    // Start the first process
    kill(processes[current_process], SIGCONT);
    process_states[current_process].running  = 1;

    // Wait for all application processes to finish
    for (int i = 0; i < num_processes; i++)
    {
        waitpid(processes[i], NULL, 0);
    }

    // Finish the  InterController Sim
    kill(controller_pid, SIGTERM);
    printf("KernelSim -- All Aplications process ar over. \n");
    exit(0);
}

void Inter_controller_sim() 
{
    srand(time(NULL));
    while (1) 
    {
        usleep(TIME_SLICE); 
        kill(kernel_pid, SIGALRM); 

        
        if ((rand() % 100) < (P_1 * 100))
        {
            kill(kernel_pid, SIGUSR1); 
        }
        if ((rand() % 100) < (P_2 * 100)) 
        {
            kill(kernel_pid, SIGUSR2); 
        }
    }
}








void Handle_irq0(int sig) 
{
    process_states[current_process].program_counter++;
    if (process_states[current_process].running== 1)
    {
        kill(processes[current_process], SIGSTOP);
        process_states[current_process].running = 0;
    }

    int prev_process = current_process;
    do 
    {
        current_process = (current_process + 1) % num_processes;
    } while (process_states[current_process].status != 0);

    kill(processes[current_process], SIGCONT);
    process_states[current_process].running = 1;

    printf("KernelSim: Process %d suspended, switching to process %d\n", prev_process + 1, current_process + 1);
}

void Handle_irq1(int sig)
 {
    for (int i = 0; i < num_processes; i++) 
    {
        if (process_states[i].status == 1) 
        {
            process_states[i].status = 0;
            printf("KernelSim: Unlocked the process %d that was waiting for D1\n", i + 1);
            if (process_states[i].running == 0) {
                kill(processes[i], SIGCONT);
                process_states[i].running = 1;
            }
        }
    }
}

void Handle_irq2(int sig) 
{
    for (int i = 0; i < num_processes; i++) 
    {
        if (process_states[i].status == 2) 
        {
            process_states[i].status = 0;
            printf("KernelSim: Unlocked the process %d that was waiting for D2\n", i + 1);
            if (process_states[i].running == 0) 
            {
                kill(processes[i], SIGCONT);
                process_states[i].running = 1;
            }
        }
    }
}



void Application_process(int id) 
{
    srand(time(NULL) + getpid());
    while (1) 
    {
        usleep(TIME_SLICE); // Simulate the exectuion

        if (rand() % 100 < 15) { // choose the system call 
            int device = rand() % 2; // 0 for D1, 1 for D2
            printf("Process:  %d: syscall(D%d)\n", id, device + 1);

            // change the process status.
            process_states[id - 1].status = device + 1;
            if (device == 0) process_states[id - 1].acess_count_d1++;
            else process_states[id - 1].acess_count_d2++;

            raise(device == 0 ? SIGUSR1 : SIGUSR2); // Sends a signal to KernelSim.
            pause(); // Waits to be unlocked.
        }

        if (process_states[id - 1].program_counter < MAX_ITERATIONS) {
            process_states[id - 1].program_counter++;
        } else {
            process_states[id - 1].finished = 1;
            exit(0); // Process over.
        }
    }
}