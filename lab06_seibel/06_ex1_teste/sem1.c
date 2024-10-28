#include "mysem.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define TRUE 		1
#define NUM_PRC		2
#define BUF_SIZ 	200
#define MSG_NUM 	100

static void error(const char* msg);
void 		writing_finished(int signal);

char* shmptr;

int main(void)
{
	pid_t
		sender,
		receiver;
	
	int
		has_read,
		has_written,
		shmid,
		status,
		i = 0;

	if ((has_read = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL)) == -1)
		error("semget");
	sem_setval(has_read, 0, 1);

	if ((has_written = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL)) == -1)
		error("semget");
	sem_setval(has_written, 0, 0);

	if ((shmid = shmget(IPC_PRIVATE, BUF_SIZ, IPC_CREAT | S_IRWXU)) == -1)
	       error("shmget");

	if ((shmptr = (char*)shmat(shmid, NULL, 0)) == (void*)-1)
		error("shmat");	

	if ((receiver = fork()) < 0) // Receiver
		error("fork");
	else if (receiver == 0)
	{
		signal(SIGINT, writing_finished);

		while (TRUE)
		{
			sem_down(has_written, 0);
			printf("%s\n", shmptr);
			usleep(250);
			sem_up(has_read, 0);
		}

		shmdt(shmptr);
		exit(EXIT_SUCCESS);
	}

	if ((sender = fork()) < 0) // Error
		error("fork");
	else if (sender == 0) // Sender code
	{
		while (i < MSG_NUM)
		{
			sem_down(has_read, 0);
			sprintf(shmptr, "message %d", ++i);
			usleep(250);
			sem_up(has_written, 0);
		}
		
		kill(receiver, SIGINT);
		shmdt(shmptr);
		exit(EXIT_SUCCESS);
	}

	for (int i = 0; i < NUM_PRC; i++)
		wait(&status);

	semctl(has_written, 0, IPC_RMID);
	semctl(has_read, 0, IPC_RMID);
	shmdt(shmptr);
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}

static void error(const char* msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void writing_finished(int signal)
{
	printf("%s\n", shmptr);
	shmdt(shmptr);
	
	exit(EXIT_SUCCESS);
}
