// my_pipe util1 arg arg | util2 arg arg | ...

#include <fcntl.h>      // open
#include <stdio.h>
#include <stdlib.h>     // remove
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>     // close, dup, dup2

#define error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define FD_STDIN    0
#define FD_STDOUT   1
#define FILE        "temp"
#define PARSER      "|"

/**
 * Implements Unix's pipe.
 */
int main(int argc, char** argv)
{
    pid_t   pid;                // Process ID.
   
    int     status,             // Auxiliar variable used in wait().
            prevfd = FD_STDIN,  // Previous file descriptor.
            currfd,             // Current file descriptor.
            stdout_fd;          // File descriptor to stdout (terminal).
    
    size_t  offset = 1,         // Current index of argv.
            
    /* 
        Number of elements in the current program's params array.
        Has to be at least 1 as it includes the program's name.
    */
            size = 1;

    // Duplicates reference to stdout for later use
    stdout_fd = dup(FD_STDOUT);

    while (offset < argc)
    {
        // Parses params array of the current program
        while (argv[offset + size] && strcmp(argv[offset + size], PARSER))
            size++;

        // argv[i] == NULL indicates end of argv and, thus, last program

        if (argv[offset + size]) // Intermediate outputs should be redirected to temp file
        {
            argv[offset + size] = NULL;

            if ((currfd = open(FILE, O_CREAT | O_RDWR | O_TRUNC, __S_IREAD | __S_IWRITE)) == -1)
                error("open");

            dup2(currfd, FD_STDOUT); // Redirects output to temp file
        }

        else // Last output should be to stdout (terminal)
            dup2(stdout_fd, FD_STDOUT);

        // Creates pipe
        dup2(prevfd, FD_STDIN); // Redirects input to previous temp file

        // Executes program
        if ((pid = fork()) < 0) // Fork error
            error("fork");

        else if (pid == 0) // Executes current program
        {
            if (execvp(argv[offset], argv + offset) == -1)
                error("exec");
        }
        wait(&status);

        // Resets variables for next program
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
        Act.: OK.
    
*/
