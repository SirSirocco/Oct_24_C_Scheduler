// Versao 1.0: 16.7kB

#include "my_msg.h"
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define PRC_NUM     2
#define BUF_SIZE    16
#define MSG_NUM     64
#define TYPE_SND    1
#define TYPE_RCV    2
#define RCV_SEM		"has read"
#define SND_SEM		"has written"

static void error(const char* msg);
sem_t*      sem_open_wrapper(const char* name, unsigned int val);

int main(void)
{
    pid_t   sender, receiver;
    sem_t   *sem_rcv, *sem_snd;
    int     msqid, msg_count = 0, status;
    Message msg;

    // Aloca semaforos
    sem_rcv = sem_open_wrapper(RCV_SEM, 1);
    sem_snd = sem_open_wrapper(SND_SEM, 0);

    // Aloca fila de mensagens
    if ((msqid = msgget(IPC_PRIVATE, 0666)) == -1)
        error("msgget");

    if ((sender = fork()) < 0) // Erro
        error("sender");
    else if (sender == 0) // Sender
    {
        msg.mtype = TYPE_SND;
        sprintf(msg.mtext, "snd%d", ++msg_count);

        sem_wait(sem_rcv);
        msgsnd(msqid, &msg, MSG_SIZE, 0);
        sem_post(sem_snd);

        while (msg_count < MSG_NUM)
        {
            sem_wait(sem_rcv);
            msgrcv(msqid, &msg, MSG_SIZE, TYPE_RCV, 0);
            printf("Snder recebeu: %s\n", msg.mtext);

            msg.mtype = TYPE_SND;
            sprintf(msg.mtext, "snd%d", ++msg_count);
            
            msgsnd(msqid, &msg, MSG_SIZE, 0);
            sem_post(sem_snd);
        }

        sem_close(sem_snd);
        sem_close(sem_rcv);
        exit(EXIT_SUCCESS);
    }

    if ((receiver = fork()) < 0) // Erro
        error("receiver");
    else if (receiver == 0) // Receiver
    {
        while (msg_count < MSG_NUM)
        {
            sem_wait(sem_snd);
            msgrcv(msqid, &msg, MSG_SIZE, TYPE_SND, 0);
            printf("Rcver recebeu: %s\n", msg.mtext);

            msg.mtype = TYPE_RCV;
            sprintf(msg.mtext, "rcv%d", ++msg_count);

            msgsnd(msqid, &msg, MSG_SIZE, 0);
            sem_post(sem_rcv);
        }

        sem_close(sem_snd);
        sem_close(sem_rcv);
        exit(EXIT_SUCCESS);
    }

    for (int i = 0; i < PRC_NUM; i++)
        wait(&status);
    
    // Remove semaforos
    sem_close(sem_rcv);
    sem_unlink(RCV_SEM);
    sem_close(sem_snd);
    sem_unlink(SND_SEM);

    // Remove fila de mensagens
    msgctl(msqid, IPC_RMID, NULL);

    return 0;
}

static void error(const char* msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

sem_t* sem_open_wrapper(const char* name, unsigned int val)
{
	sem_t* sem;

	if ((sem = sem_open(name, O_CREAT | O_EXCL, S_IRWXU, val)) == SEM_FAILED)
		error("sem_open");

	return sem;
}
