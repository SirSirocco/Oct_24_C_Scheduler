#include <sys/msg.h>

#define MSG_SIZE 16 // byte(s). Tamanho maximo de uma mensagem (buffer).

// Os nomes dos campos da struct sao arbitrarios, mas nao os tipos
struct message
{
    long int    mtype;
    char        mtext[MSG_SIZE];
};

typedef struct message Message;
