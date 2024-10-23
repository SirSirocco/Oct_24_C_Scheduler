#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
};

// Função para inicializar o valor do semáforo
int setSemValue(int semId) {
    union semun semUnion;
    semUnion.val = 1;
    return semctl(semId, 0, SETVAL, semUnion);
}

// Função para remover o semáforo
void delSemValue(int semId) {
    union semun semUnion;
    semctl(semId, 0, IPC_RMID, semUnion);
}

// Operação P (down)
int semaforoP(int semId) {
    struct sembuf semB;
    semB.sem_num = 0;
    semB.sem_op = -1;  // P (decrementa o semáforo)
    semB.sem_flg = SEM_UNDO;
    semop(semId, &semB, 1);
    return 0;
}

// Operação V (up)
int semaforoV(int semId) {
    struct sembuf semB;
    semB.sem_num = 0;
    semB.sem_op = 1;  // V (incrementa o semáforo)
    semB.sem_flg = SEM_UNDO;
    semop(semId, &semB, 1);
    return 0;
}

int main(int argc, char *argv[]) {
    int i;
    char letra = 'o';
    int semId;

    // Verifica se o semáforo já foi criado
    if (argc > 1) {
        semId = semget(8752, 1, 0666 | IPC_CREAT); // Cria o semáforo
        setSemValue(semId);
        letra = 'x';
        sleep(2);
    } else {
        while ((semId = semget(8752, 1, 0666)) < 0) {
            putchar('.'); fflush(stdout);
            sleep(1);
        }
    }

    // Executa 10 loops com operação P e V
    for (i = 0; i < 10; i++) {
        semaforoP(semId);  // Entra na região crítica
        putchar(toupper(letra)); fflush(stdout);
        sleep(rand() % 3); // Simula trabalho na região crítica
        putchar(letra); fflush(stdout);
        semaforoV(semId);  // Sai da região crítica
        sleep(rand() % 2);
    }

    printf("\nProcesso %d terminou\n", getpid());

    // Se o semáforo foi criado por este processo, remove-o
    if (argc > 1) {
        sleep(10);
        delSemValue(semId);
    }

    return 0;
}
