#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <string.h>

// Função para calcular a idade em dias a partir da última modificação
int calcular_idade(time_t modificacao) 
{
    time_t agora = time(NULL);  // Obtém o tempo atual
    return (agora - modificacao) / (60 * 60 * 24);  // Converte segundos para dias
}

int main() 
{
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    char path[1024];

    // Abrindo o diretório atual
    dir = opendir(".");
    if (dir == NULL) {
        perror("Erro ao abrir o diretório");
        return 1;
    }

    printf("Number of files = \n");

    // Percorrendo os arquivos do diretório
    while ((entry = readdir(dir)) != NULL) 
    {
        // Ignorando "." e ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) 
        {
            continue;
        }

        // Construindo o caminho completo do arquivo
        snprintf(path, sizeof(path), "./%s", entry->d_name);

        // Obtendo informações do arquivo usando stat()
        if (stat(path, &fileStat) == 0) 
        {
            // Exibindo as informações do arquivo
            printf("%s    inode: %ld    size: %ld bytes    age: %d days\n", 
                   entry->d_name, fileStat.st_ino, fileStat.st_size, calcular_idade(fileStat.st_mtime));
        } else {
            perror("Erro ao obter informações do arquivo");
        }
    }

    // Fechando o diretório
    closedir(dir);

    return 0;
}
