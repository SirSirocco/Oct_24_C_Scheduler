#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>


#define SHM_SIZE 1024
#define KEY1 8752

typedef struct
{
    int value;
    int sequence;
} SharedData;

int main(void) {
    int shmid = shmget(KEY1, SHM_SIZE, 0666), sleep_time;
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }
    
    SharedData* m1 = (SharedData*)shmat(shmid, NULL, 0);
    if (m1 == (void*)-1) {
        perror("shmat");
        exit(1);
    }
    
    // Use uma combinação de tempo e PID para a semente
    srand(time(NULL) ^ (getpid() << 16));
    
    while (1)
    {
        sleep_time = rand() % 5 + 1;
        sleep(sleep_time);
        m1->value = rand() % 100;
        m1->sequence++;
        printf("P1 (PID %d) dormiu por %d segundos e gerou: %d\n", getpid(), sleep_time, m1->value);
    }
    
    return 0;
}
