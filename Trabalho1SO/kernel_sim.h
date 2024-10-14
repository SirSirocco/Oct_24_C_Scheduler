#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>




#define TIME_SLICE 300000 // 0.3 s
#define MAX_ITERATIONS 8  // Iterations process number.
#define P_1 0.1 // IRQ1 (D1) Probabilistic.
#define P_2 0.05 // IRQ2 (D2) Probabilistic.
#define MIN_PROCESSES 3
#define MAX_PROCESSES 5

// Data struct I used in the program.
typedef struct 
{   
    int acess_count_d1;
    int acess_count_d2;
    int ID;
    pid_t pid;
    int program_counter;
    int status; // 0: executing, 1: blocking D1, 2: blocking D2
    int running; // 1 -> running, 0-> not running.           (Like a bool number.)
    int finished; // 1 -> finished , 0--> not finished.
} ProcessState;

//Global vars

extern pid_t kernel_pid, controller_pid;
extern pid_t *processes;
extern ProcessState *process_states;
extern int num_processes;
extern int current_process;




// All functions I used are here.
void Handle_sigint(int sig);
void Kernel_sim();
void Inter_controller_sim();
void Application_process(int id);
void Handle_irq0(int sig);
void Handle_irq1(int sig);
void Handle_irq2(int sig);
