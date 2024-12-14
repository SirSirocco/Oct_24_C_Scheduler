#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>	// sem_t and semaphore operations; easier than <sys/sem.h>
#include <fcntl.h>		// file control: O_OPEN, O_EXCL
#include <signal.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define TRUE 		1
#define NUM_PRC		2				// Number of processes.
#define BUF_SIZ 	200				// Number of bytes of message buffer.
#define MSG_NUM 	128				// Number of messages.
#define MAX_MSG_NUM 8
#define MAX_MSG_SIZ 20

/* SEMAPHORE NAMES */
#define R_SEM		"has read"		// Mutex that indicates receiver has read.
#define W_SEM		"has written"	// Mutex that indicates sender has written.

/* SEMAPHORE INITIAL VALUES */
#define R_INI_VAL (MAX_MSG_NUM) // Allows sender to write first.
#define W_INI_VAL 0	// Blocks receiver until sender has written first message.

/* PROTOTYPES */
static void error(const char* msg);
sem_t*		sem_open_wrapper(const char* name, unsigned int val);
void 		shm_alloc_at(int* shmid, char** shmptr);
void 		dettach_resources(void);
void 		free_resources(int shmid);

/* GLOBAL VARS */
char* shmptr; // Pointer to base of shared memory.
sem_t *has_read, *has_written;

int main(void)
{
	pid_t sender, receiver;
	int shmid, status, i = 0, msg_count = 0;

	// Resource allocation and attachment
	shm_alloc_at(&shmid, &shmptr);
	has_read = sem_open_wrapper(R_SEM, R_INI_VAL);
	has_written = sem_open_wrapper(W_SEM, W_INI_VAL);

	/* RECEIVER */
	if ((receiver = fork()) < 0) // Error
		error("fork");
	
	else if (receiver == 0) // Receiver's code
	{
		while (TRUE)
		{
			sem_wait(has_written); 	                    // While sender has not written, waits
			printf("%s\n", shmptr + MAX_MSG_SIZ * i);	// Reads

            if (++msg_count == MSG_NUM)
                break;
            
            i = (i + 1) % MAX_MSG_NUM;					// Cycles through buffer
			sem_post(has_read);		                    // Tells sender that receiver has read
		}

		dettach_resources();
		exit(EXIT_SUCCESS);
	}

	/* SENDER */
	if ((sender = fork()) < 0) // Error
		error("fork");
	
	else if (sender == 0) // Sender's code
	{
		while (msg_count < MSG_NUM)
		{
			sem_wait(has_read); 						                    // While receiver has not read, waits
			sprintf(shmptr + i * MAX_MSG_SIZ, "mensagem %d", ++msg_count);  // Writes
            i = (i + 1) % MAX_MSG_NUM;            							// Cycles through buffer
			sem_post(has_written); 						                    // Tells receiver that sender has written
		}

		dettach_resources();

		exit(EXIT_SUCCESS);
	}

	for (int j = 0; j < NUM_PRC; j++) // Parent waits child processes finish
		wait(&status);

	dettach_resources();
	free_resources(shmid);

	return 0;
}

// Prints error message and terminates the program.
static void error(const char* msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

// Simplifies the creation of a new semaphore.
sem_t* sem_open_wrapper(const char* name, unsigned int val)
{
	sem_t* sem;

	if ((sem = sem_open(name, O_CREAT | O_EXCL, S_IRWXU, val)) == SEM_FAILED)
		error("sem_open");

	return sem;
}

// Simplifies the creation of a new shared memory segment.
void shm_alloc_at(int* shmid, char** shmptr)
{
	if ((*shmid = shmget(IPC_PRIVATE, BUF_SIZ, IPC_CREAT | S_IRWXU)) == -1)
		error("shmget");

	if ((*shmptr = (char*)shmat(*shmid, NULL, 0)) == (void*)-1)
		error("shmat");	
}

// Dettach from allocated resources.
void dettach_resources(void)
{
	shmdt(shmptr);
    sem_close(has_read);
	sem_close(has_written);
}

// Frees all alocated resources.
void free_resources(int shmid)
{
	shmctl(shmid, IPC_RMID, NULL);
    sem_unlink(R_SEM);
    sem_unlink(W_SEM);
}
