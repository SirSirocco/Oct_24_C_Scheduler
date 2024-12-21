#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>     // pipe, write

#define error(msg)  do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define READ        0
#define WRITE       1
#define STDIN_FD    0

#define MSG_CHLD    "Darth, I am your son.\n"
#define NUM_FD      2
#define NUM_CHLD    1
#define SIZ_BUF     64

int main(void)
{
    pid_t       pid;
    int         status, 
                fd[NUM_FD]; // File descriptors.
    const char  message[] = MSG_CHLD;
    char        buf[SIZ_BUF];
    ssize_t     bytenum;

    if (pipe(fd) == -1) // Pipe error
        error("pipe");

    if ((pid = fork()) < 0) // Fork error
        error("fork");

    else if (pid == 0) // Child
    {
        write(fd[WRITE], message, strlen(message) + 1); // + 1 to include '\0'
        exit(EXIT_SUCCESS);
    }

    for (int i = 0; i < NUM_CHLD; i++)
        wait(&status);

    /*
        Let's see if an error will be raised
        as SIZ_BUF > strlen(message) + 1.
    */
    bytenum = read(fd[READ], buf, SIZ_BUF);
    write(STDIN_FD, buf, bytenum);

    return EXIT_SUCCESS;
}
