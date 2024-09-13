#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>  

int main() {
    int fd[2]; 

    pid_t pid;
    char buffer[1024];
    ssize_t bytesRead;

   
    if (pipe(fd) == -1) 
    {
        perror("Erro ao criar o pipe");
        exit(1);
    }

   
    pid = fork();

    if (pid < 0) 
    {
        perror("Erro no fork");
        exit(1);
    }

    if (pid > 0) 
    {
        
        close(fd[0]); 

        
        int inputFile = open("entrada.txt", O_RDONLY);
        if (inputFile < 0) 
        {
            perror("Erro ao abrir o arquivo de entrada");
            exit(1);
        }

        
        while ((bytesRead = read(inputFile, buffer, sizeof(buffer))) > 0) 
        {
            if (write(fd[1], buffer, bytesRead) != bytesRead) 
            {
                perror("Erro ao escrever no pipe");
                close(inputFile);
                close(fd[1]);
                exit(1);
            }
        }

       
        close(inputFile);
        close(fd[1]);

        
        wait(NULL);
    } else 
    {
        
        close(fd[1]); 
       
        int outputFile = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outputFile < 0) 
        {
            perror("Erro ao abrir o arquivo de saída");
            exit(1);
        }

       
        while ((bytesRead = read(fd[0], buffer, sizeof(buffer))) > 0)
         {
            if (write(outputFile, buffer, bytesRead) != bytesRead)
             {
                perror("Erro ao escrever no arquivo de saída");
                close(outputFile);
                close(fd[0]);
                exit(1);
            }
        }

       
        close(outputFile);
        close(fd[0]);

        exit(0);
    }

    return 0;
}
