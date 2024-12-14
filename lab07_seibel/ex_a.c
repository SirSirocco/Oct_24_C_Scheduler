#include "my_msg.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define PRC_NUM     2   // Numero de processos.
#define MSG_NUM     64  // Numero total de mensagens.
#define TYPE_SND    1   // Identificador das mensagens enviadas pelo sender.
#define TYPE_RCV    2   // Identificador das mensagens enviadas pelo receiver.

static void error(const char* msg);

int main(void)
{
    pid_t   sender, receiver;
    int     msqid, msg_count = 0, status;
    Message msg;

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

            msgrcv(msqid, &msg, MSG_SIZE, TYPE_RCV, 0); // *** Recebe mensagem de replica, atualizando os dois campos de msg
            printf("Snder recebeu: %s\n", msg.mtext);
        }

        exit(EXIT_SUCCESS);
    }

    if ((receiver = fork()) < 0) // Erro
        error("receiver");
    else if (receiver == 0) // Receiver
    {
        while (msg_count < MSG_NUM)
        {
            msgrcv(msqid, &msg, MSG_SIZE, TYPE_SND, 0); // *** Recebe mensagem, atualizando os dois campos de msg
            printf("Rcver recebeu: %s\n", msg.mtext);
            
            // Formula mensagem de replica
            msg.mtype = TYPE_RCV;                       // Necessario por causa de ***
            sprintf(msg.mtext, "rcv%d", ++msg_count);
            msgsnd(msqid, &msg, MSG_SIZE, 0);           // Envia replica
        }

        exit(EXIT_SUCCESS);
    }

    // Espera filhos terminarem
    for (int i = 0; i < PRC_NUM; i++)
        wait(&status);

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
