
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd[2]; 
    pid_t pid;
    char mensagem[] = "Olá, Pai!";
    char buffer[100];

    
    if (pipe(fd) == -1) {
        perror("Erro ao criar o pipe");
        exit(1);
    }

    
    pid = fork();

    if (pid < 0) {
        perror("Erro no fork");
        exit(1);
    }

    if (pid > 0) {
        
        close(fd[1]); 
        read(fd[0], buffer, sizeof(buffer)); 
        printf("Pai leu: %s\n", buffer);
        close(fd[0]); 
    } else {
     
        close(fd[0]); 
        write(fd[1], mensagem, strlen(mensagem) + 1); 
        printf("Filho escreveu: %s\n", mensagem);
        close(fd[1]); 
        exit(0);
    }

    return 0;
}