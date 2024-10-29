#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

// Função recursiva para percorrer diretórios e somar os tamanhos dos arquivos
long long soma_tamanhos_diretorio(const char *dir_name) 
{
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    char path[1024];
    long long total_size = 0;

    // Abrindo o diretório
    dir = opendir(dir_name);
    if (dir == NULL) {
        perror("Erro ao abrir o diretório");
        return 0;
    }

    // Percorrendo as entradas do diretório
    while ((entry = readdir(dir)) != NULL) 
    {
        // Ignorando as entradas "." e ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construindo o caminho completo
        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);

        // Obtendo informações do arquivo
        if (stat(path, &fileStat) == 0) 
        {
            // Verificando se é um diretório
            if (S_ISDIR(fileStat.st_mode)) 
            {
                // Se for um diretório, chamamos a função recursivamente
                total_size += soma_tamanhos_diretorio(path);
            } else {
                // Se for um arquivo, somamos o tamanho
                total_size += fileStat.st_size;
            }
        } else 
        {
            perror("Erro ao obter informações do arquivo");
        }
    }

    // Fechando o diretório
    closedir(dir);

    return total_size;
}

int main() 
{
    long long total_size;

    // Calculando o tamanho total dos arquivos no diretório atual
    total_size = soma_tamanhos_diretorio(".");

    printf("Tamanho total dos arquivos: %lld bytes\n", total_size);

    return 0;
}
