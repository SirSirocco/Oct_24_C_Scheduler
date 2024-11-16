#include "my_msg.h"
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define PRC_NUM     2   // Numero de processos.
#define BUF_SIZE    16  // Tamanho maximo de uma mensagem (buffer).
#define MSG_NUM     64  // Numero total de mensagens.
#define TYPE_SND    1   // Identificador de mensagens enviados pelo sender.
#define TYPE_RCV    2   // Identificador de mensagens enviados pelo receiver.
#define RCV_SEM		"has read"      // Indica que receiver leu.
#define SND_SEM		"has written"   // Indica que sender escreveu.

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
    if ((msqid = msgget(IPC_PRIVATE, S_IRWXU)) == -1)
        error("msgget");

    if ((sender = fork()) < 0) // Erro
        error("sender");
    else if (sender == 0) // Sender
    {
        while (msg_count < MSG_NUM)
        {
            // Formula mensagem a ser enviada
            msg.mtype = TYPE_SND;                       // Necessario por causa de ***
            sprintf(msg.mtext, "msg%d", ++msg_count);

            msgsnd(msqid, &msg, MSG_SIZE, 0);           // Envia mensagem
            sem_post(sem_snd);                          // Avisa que escreveu
            
            sem_wait(sem_rcv);                          // Espera receiver ler e escrever replica
            msgrcv(msqid, &msg, MSG_SIZE, TYPE_RCV, 0); // *** Recebe mensagem de replica, atualizando os dois campos de msg
            
            printf("Snder recebeu: %s\n", msg.mtext);
        }
        // Desanexa semaforos
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
            sem_wait(sem_snd);                          // Espera sender enviar
            msgrcv(msqid, &msg, MSG_SIZE, TYPE_SND, 0); // *** Recebe mensagem, atualizando os dois campos de msg
            
            printf("Rcver recebeu: %s\n", msg.mtext);

            // Formula mensagem de replica
            msg.mtype = TYPE_RCV;                       // Necessario por causa de ***
            sprintf(msg.mtext, "rcv%d", ++msg_count);
            
            msgsnd(msqid, &msg, MSG_SIZE, 0);           // Envia replica
            sem_post(sem_rcv);                          // Avisa que leu e escreveu replica
        }
        // Desanexa semaforos
        sem_close(sem_snd);
        sem_close(sem_rcv);
        
        exit(EXIT_SUCCESS);
    }

    // Espera filhos terminarem
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

// Exibe mensagem de erro e encerra com exit.
static void error(const char* msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

// Simplifica a criacao de um novo semaforo.
sem_t* sem_open_wrapper(const char* name, unsigned int val)
{
	sem_t* sem;

	if ((sem = sem_open(name, O_CREAT | O_EXCL, S_IRWXU, val)) == SEM_FAILED)
		error("sem_open");

	return sem;
}
