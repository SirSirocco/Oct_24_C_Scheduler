#include "mysem.h"

union semun
{
    int             val;
    struct sem_ds*  buf;
    unsigned short* array;
};

// Sets val as value of semaphore of index semnum with id semid.
int sem_setval(int semid, int semnum, int val)
{
    union semun semunion;

    semunion.val = val;

    return semctl(semid, semnum, SETVAL, semunion);
}

// Decrementsts semaphore semid[semnum] by 1.
int sem_down(int semid, int semnum)
{
    struct sembuf down = { semnum, -1, SEM_UNDO };
    return semop(semid, &down, 1);
}

// Increments semaphore semid[semnum] by 1.
int sem_up(int semid, int semnum)
{
    struct sembuf up = { semnum, +1, SEM_UNDO };
    return semop(semid, &up, 1);
}
