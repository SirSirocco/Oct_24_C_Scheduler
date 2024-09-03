/* Pedro de Almeida Barizon 2211350 */

#include <errno.h>      // errno, ENOENT
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int pid, status;
    if (argc < 2) // Se usuario nao passou executavel, encerra com erro
    {
        errno = ENOENT; // "No such file or directory"
        perror("minhashell");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0) // Erro
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) // Filho
    {
        execvp(argv[1], argv + 1); // Executa a partir do segundo argumento de argv
    }
    else // Pai
    {
        waitpid(pid, &status, 0); // Pai espera filho terminar
    }

    return 0;
}
