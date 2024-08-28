// pai.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

#define SHM_SIZE 1024
#define KEY1 8752
#define KEY2 8753

typedef struct {
    int value;
    int sequence;
} SharedData;

int main() {
    int shmid1 = shmget(KEY1, SHM_SIZE, IPC_CREAT | 0666);
    int shmid2 = shmget(KEY2, SHM_SIZE, IPC_CREAT | 0666);
    
    if (shmid1 == -1 || shmid2 == -1) {
        perror("shmget");
        exit(1);
    }
    
    SharedData *m1 = (SharedData *)shmat(shmid1, NULL, 0);
    SharedData *m2 = (SharedData *)shmat(shmid2, NULL, 0);
    
    if (m1 == (void *)-1 || m2 == (void *)-1) {
        perror("shmat");
        exit(1);
    }
    
    m1->sequence = 0;
    m2->sequence = 0;

    if (fork() == 0) {
        execl("./p1", "p1", NULL);
    }
    
    if (fork() == 0) {
        execl("./p2", "p2", NULL);
    }
    
    int last_seq1 = 0, last_seq2 = 0;
    
    while (1) {
        if (m1->sequence > last_seq1 && m2->sequence > last_seq2) {
            printf("Produto: %d\n\n", m1->value * m2->value);
            last_seq1 = m1->sequence;
            last_seq2 = m2->sequence;
        }
        usleep(100000);  // Sleep for 100ms
    }
    
    return 0;
}