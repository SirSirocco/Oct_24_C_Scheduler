#include "my_msg.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define PRC_NUM     2   // Numero de processos.
#define AUX_SIZE    3   // Numero de bytes necessarios para escrever "msg".
#define MAX_QMSG    8   // Numero maximo de mensagens na fila por vez.
#define MSG_NUM     64  // Numero total de mensagens a serem enviadas.
#define TYPE_SND    1   // Identificador das mensagens enviadas pelo sender.

static void error(const char* msg);
void        msqid_get_status(int msqid, struct msqid_ds* buf);
void        msqid_set(int msqid, struct msqid_ds* buf);

int main(void)
{
    pid_t           sender, receiver;
    int             msqid, msg_count = 0, status;
    struct msqid_ds queue_attr;
    Message         msg;

    // Aloca fila de mensagens
    if ((msqid = msgget(IPC_PRIVATE, S_IRWXU)) == -1)
        error("msgget");

    // Obtem status da fila de mensagens (necessario para realizar msqid_set)
    msqid_get_status(msqid, &queue_attr);

    /*
        Define numero maximo de mensagens na fila indiretamente ao
        estabelecer numero maximo de bytes (qbytes).
    */
    queue_attr.msg_qbytes = MAX_QMSG * MSG_SIZE;
    msqid_set(msqid, &queue_attr);

    if ((sender = fork()) < 0) // Erro
        error("sender");
    else if (sender == 0) // Sender
    {
        msg.mtype = TYPE_SND;                           // Define tipo da mensagem

        while (msg_count < MSG_NUM)
        {
            sprintf(msg.mtext, "msg%d", ++msg_count);   // Formula mensagem
            msgsnd(msqid, &msg, MSG_SIZE, 0);           // Envia mensagem

            msqid_get_status(msqid, &queue_attr);       // Obtem numero atual de mensagens na fila (msg_qnum)
            if (queue_attr.msg_qnum > MAX_QMSG)         // Se ultrapassar limite, exibe aviso
                printf("\n*** FILA EXCEDEU LIMITE DE MENSAGES ***\n\n");
        }

        exit(EXIT_SUCCESS);
    }

    if ((receiver = fork()) < 0) // Erro
        error("receiver");
    else if (receiver == 0) // Receiver
    {
        while (msg_count < MSG_NUM)
        {
            msgrcv(msqid, &msg, MSG_SIZE, TYPE_SND, 0); // Recebe mensagem
            msg_count = atoi(msg.mtext + AUX_SIZE);     // Atualiza contador com base no valor recebido
            printf("Rcver recebeu: %s\n", msg.mtext);
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

// Atribui status da fila de mensagens a buf.
// Necessario para que o IPC_SET funcione adequamente.
void msqid_get_status(int msqid, struct msqid_ds* buf)
{
    if (msgctl(msqid, IPC_STAT, buf) == -1)
        error("IPC_STAT");
}

// Atualiza atributos da fila de mensagens via IPC_SET
// com base nos campos de buf.
void msqid_set(int msqid, struct msqid_ds* buf)
{
    if (msgctl(msqid, IPC_SET, buf) == -1)
        error("IPC_SET");
}
