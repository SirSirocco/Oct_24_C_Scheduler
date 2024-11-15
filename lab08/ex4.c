#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

// Função recursiva para percorrer diretórios e arquivos, imprimindo com indentação
void listar_diretorios_arquivos(const char *dir_name, int level)
 {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    char path[1024];

    // Abrindo o diretório
    dir = opendir(dir_name);
    if (dir == NULL) 
    {
        perror("Erro ao abrir o diretório");
        return;
    }

    // Percorrendo as entradas do diretório
    while ((entry = readdir(dir)) != NULL)
     {
        // Ignorando "." e ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) 
        {
            continue;
        }

        // Construindo o caminho completo
        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);

        // Obtendo informações do arquivo
        if (stat(path, &fileStat) == 0) 
        {
            // Imprimindo o nome com indentação
            printf("%*s[%s]\n", level * 2, "", entry->d_name);

            // Se for um diretório, chamar a função recursivamente
            if (S_ISDIR(fileStat.st_mode)) {
                listar_diretorios_arquivos(path, level + 1);
            }
        } else 
        {
            perror("Erro ao obter informações do arquivo");
        }
    }

    // Fechando o diretório
    closedir(dir);
}

int main() 
{
    // Começando a partir do diretório atual (".") e no nível de recursão 0
    listar_diretorios_arquivos(".", 0);

    return 0;
}
