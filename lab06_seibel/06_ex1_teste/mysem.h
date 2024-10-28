#include <sys/sem.h>

int sem_setval(int semid, int semnum, int val);
int sem_down(int semid, int semnum);
int sem_up(int semid, int semnum);