#include "sim_virtual.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MB_TO_kB    (size_t)pow(2.0, 10.0)
#define LOG2_kB     (size_t)10
#define BUF_SIZ     128
#define SUCCESS     0
#define error(msg)  do { perror(msg); exit(EXIT_FAILURE); } while (0)

char    file_name[BUF_SIZ] = {'.', '/', '\0'};
char*   subs_method;

FILE*   file;

size_t  mem_size;
size_t  offset;
size_t  page_size;

int     page_num;
int     page_fault_count = 0;
int     page_write_count = 0;
int     time = 0;

int main(int argc, char** argv)
{
    get_data(argc, argv);
    process_data();


    log_result();

    return SUCCESS;
}

static void str_toupper(char* s)
{
    while ((*s = toupper(*s)))
        s++;
}

void get_data(int argc, char** argv)
{
    for (int i = 0; i < argc; i++)
    {
        switch (i)
        {
        case 1:
            subs_method = argv[i];
            str_toupper(subs_method); // We use toupper for uniformity
            printf("subs_method: %s\n", subs_method);
            break;

        case 2:
            strcpy(file_name, argv[i]);
            printf("file_name: %s\n", file_name);
            break;

        case 3:
            page_size = atoi(argv[i]);
            printf("page_size: %lu\n", page_size);
            break;

        case 4:
            mem_size = atoi(argv[i]);
            printf("mem_size: %lu\n", mem_size);
            break;
        }
    }
}

void process_data()
{
    // Tries to open file
    if (!(file = fopen(file_name, "r")))
        error("fopen");
    
    page_num = (mem_size * MB_TO_kB) / page_size;
    offset = LOG2_kB + (size_t)(ceil(log2(page_size)));
}

void log_result()
{
    printf("Arquivo de entrada:                     %s\n", file_name);
    printf("Tamanho da memória física:              %lu MB\n", mem_size);
    printf("Tamanho das páginas:                    %lu kB\n", page_size);
    printf("Algoritmo de substituição:              %s\n", subs_method);
    printf("Número máximo de páginas em memória:    %d\n", page_num);
    printf("Número de Faltas de Página:             %d\n", page_fault_count);
    printf("Número de Páginas Escritas:             %d\n", page_write_count);
    printf("Offset de bytes:                        %lu\n", offset);
}
