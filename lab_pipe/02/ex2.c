#include <fcntl.h> // open
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define STDIN_FD    0
#define STDOUT_FD   1
#define FIN_IDX     1
#define FOUT_IDX    2
#define CHLD_IDX    3

int main(int argc, char** argv)
{
    int     fd, status;
    pid_t   pid;

    // Redirects stdin
    if ((fd = open(argv[FIN_IDX], O_RDONLY, S_IRWXU)) == -1)
        error("open_in");
    dup2(fd, STDIN_FD);

    // Redirects stdout
    if ((fd = open(argv[FOUT_IDX], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU)) == -1)
        error("open_out");
    dup2(fd, STDOUT_FD);

    if ((pid = fork()) < 0) // Fork error
        error("fork");

    else if (pid == 0) // Child
        execv(argv[CHLD_IDX], argv + CHLD_IDX);
    
    wait(&status);

    return EXIT_SUCCESS;
}
