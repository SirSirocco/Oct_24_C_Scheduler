#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#define SHM_SIZE 1024
#define KEY2 8753

typedef struct {
    int value;
    int sequence;
} SharedData;

int main() {
    int shmid = shmget(KEY2, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    
    SharedData *m2 = (SharedData *)shmat(shmid, NULL, 0);
    if (m2 == (void *)-1) {
        perror("shmat");
        exit(1);
    }
    
    // Use uma combinação de tempo e PID para a semente
    srand(time(NULL) ^ (getpid()<<16));
    
    while (1) {
        int sleep_time = rand() % 5 + 1;
        sleep(sleep_time);
        m2->value = rand() % 100;
        m2->sequence++;
        printf("P2 (PID %d) dormiu por %d segundos e gerou: %d\n", getpid(), sleep_time, m2->value);
    }
    
    return 0;
}