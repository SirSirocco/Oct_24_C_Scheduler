#include "mysem.h"

// Sets val as max value of semaphore of index semnum with id semid.
int sem_setval(int semid, int semnum, int val)
{
    union semun
    {
        int val;
        struct semid_ds* buf;
        unsigned short* array;
    } semunion;

    semunion.val = val;

    return semctl(semid, semnum, SETVAL, semunion);
}

// Decrementsts semaphore semid[semnum] by 1.
int sem_down(int semid, int semnum)
{
    struct sembuf sops = { semnum, -1, SEM_UNDO };
    return semop(semid, &sops, 1);
}

// Increments semaphore semid[semnum] by 1.
int sem_up(int semid, int semnum)
{
    struct sembuf sops = { semnum, 1, SEM_UNDO };
    return semop(semid, &sops, 1);
}
