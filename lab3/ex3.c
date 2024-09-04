#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void childhandler(int signo);
int delay;

int main(int argc, char *argv[]) {
    pid_t pid;

    signal(SIGCHLD, childhandler);

    if ((pid = fork()) < 0) {
        fprintf(stderr, "Erro ao criar filho\n");
        exit(-1);
    }

    if (pid == 0) {
        execvp(argv[2], &argv[2]);
        fprintf(stderr, "Erro ao executar o programa filho\n");
        exit(-1);
    } else {
        sscanf(argv[1], "%d", &delay);
        sleep(delay);
        printf("Program %s exceeded limit of %d seconds!\n", argv[2], delay);
        kill(pid, SIGKILL);
        sleep(1);
    }

    return 0;
}

void childhandler(int signo) {
    int status;
    pid_t pid = wait(&status);
    printf("Child %d terminated within %d seconds with status %d.\n", pid, delay, status);
    exit(0);
}
