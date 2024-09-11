#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
 {
    int fd[2];
    pipe(fd);

    pid_t writer, reader1, reader2;

    writer = fork();
    if (writer == 0) 
    {
        close(fd[0]);
        for (int i = 1; i <= 5; i++) {
            char msg[20];
            sprintf(msg, "Mensagem %d\n", i);
            write(fd[1], msg, sizeof(msg));
            printf("Escritor escreveu: %s", msg);
            sleep(2);  // Escritor dorme 2 segundos
        }
        close(fd[1]);
        exit(0);
    }

    reader1 = fork();
    if (reader1 == 0) 
    {
        close(fd[1]);
        char buffer[100];
        while (read(fd[0], buffer, sizeof(buffer)) > 0)
         {
            printf("Leitor 1 leu: %s", buffer);
            sleep(1);  
        }
        close(fd[0]);
        exit(0);
    }

    reader2 = fork();
    if (reader2 == 0)
     {
        close(fd[1]);
        char buffer[100];
        while (read(fd[0], buffer, sizeof(buffer)) > 0) {
            printf("Leitor 2 leu: %s", buffer);
            sleep(1);  
        }
        close(fd[0]);
        exit(0);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}