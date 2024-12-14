#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define BUF_SIZ 1000
#define ALPH 26

void try_decrypt_caesar(const char* s)
{
    int j = 0;
    char buf[BUF_SIZ], ch;

    strcpy(buf, s);

    for (int i = 0; i < ALPH; i++)
    {
        printf("# OFFSET: %i\n", i);
        while ((ch = *(buf + j)) != 0)
        {
            if (isalpha(ch))
                putc((((ch - 'A') - i) + ALPH) % ALPH + 'A', stdout);
            else
                putc(ch, stdout);

            j++;
        }
        printf("\n");

        j = 0;
    }
}

int main(int argc, char** argv)
{
    char buf[BUF_SIZ];
    FILE* file;

    if (argc != 2)
        error("argv");

    if ((file = fopen(argv[1], "r")) == NULL)
        error("fopen");

    fgets(buf, BUF_SIZ, file);
    try_decrypt_caesar(buf);

    fclose(file);

    return 0;
}
