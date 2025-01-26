#include <sys/sem.h>

int     sem_setval(int semid, int semnum, int val);
void    sem_down(int semid, int semnum);
void    sem_up(int semid, int semnum);