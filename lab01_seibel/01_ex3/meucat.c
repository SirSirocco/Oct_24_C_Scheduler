/* Pedro de Almeida Barizon 2211350 */

/* DEPENDENCIAS EXTERNAS */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    FILE* file;
    int ch;

    for (int i = 1; i < argc; i++)
    {
        if (!(file = fopen(argv[i], "r"))) // Se falha de arquivo, encerra
        {
            fprintf(stderr, "meucat: %s: ", argv[i]); // Necessario usar printf por causa da string de formato, ausente em perror
            perror("");
            exit(EXIT_FAILURE);
        }
        while ((ch = fgetc(file)) != EOF)
            putc(ch, stdout); // Exibe um caractere por vez para evitar overload de buffer

        fclose(file);
    }

    return 0;
}
