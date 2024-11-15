#include <sys/msg.h>

#define MSG_SIZE 15 // byte(s)

struct message
{
    long int    mtype;
    char        mtext[MSG_SIZE];
};

typedef struct message Message;
