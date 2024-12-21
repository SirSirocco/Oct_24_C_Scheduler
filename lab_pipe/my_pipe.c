// my_pipe util1 arg arg | util2 arg arg | ...

#include <fcntl.h>      // open
#include <stdio.h>
#include <stdlib.h>     // remove
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>     // close, dup, dup2

#define error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define PARSER      "|"
#define SIZ_FILE    4096
#define FD_STDIN    0
#define FD_STDOUT   1
#define FILE        "temp"

int main(int argc, char** argv)
{
    pid_t   pid;
    int     status, prevfd = FD_STDIN, currfd, stdout_fd;
    size_t  offset = 1, size = 1;

    stdout_fd = dup(FD_STDOUT);

    while (offset < argc)
    {
        // Parses argv of the current program
        while (argv[offset + size] && strcmp(argv[offset + size], PARSER))
            size++;

        if (argv[offset + size]) // Intermediate outputs should be to temp
        {
            argv[offset + size] = NULL;
            if ((currfd = open(FILE, O_CREAT | O_RDWR | O_TRUNC, __S_IREAD | __S_IWRITE)) == -1)
                error("open");
            dup2(currfd, FD_STDOUT);
        }

        else // Last output should be to stdout
            dup2(stdout_fd, FD_STDOUT);

        // Creates pipe
        dup2(prevfd, FD_STDIN);

        // Executes program
        if ((pid = fork()) < 0) // Fork error
            error("fork");

        else if (pid == 0) // Executes current program
        {
            if (execvp(argv[offset], argv + offset) == -1)
                error("exec");
        }
        wait(&status);

        // Resets variables
        offset = size + 1;
        size = 1;

        // Resets resources
        close(prevfd);
        prevfd = currfd;
    }
    
    // Frees resources
    close(currfd);
    remove(FILE); // Removes temp file

    return EXIT_SUCCESS;
}

// TDD
/*
    Case 0: No arguments.
        Exp.: The program should do nothing.
        Act.: OK.

    Case 1: Executing a single program and then echoing it.
        S.: The first program should be executed and then its result should be exhibited
            in the console.
        V.: ./my_pipe ps | echo
        Exp.: test1.txt
    
*/
