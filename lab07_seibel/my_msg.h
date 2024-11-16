#include <sys/msg.h>

#define MSG_SIZE 15 // byte(s)

// Os nomes dos campos da struct sao arbitrarios
struct message
{
    long int    mtype;
    char        mtext[MSG_SIZE];
};

typedef struct message Message;
