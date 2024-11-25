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

char*   file_name;
char*   subs_method;

FILE*   file;

size_t  mem_size;
size_t  page_size;
size_t  offset;

int     page_num;
int     page_fault_count = 0;
int     page_write_count = 0;
int     time = 0;

int main(int argc, char** argv)
{
    get_data(argc, argv);
    configure_sim();

    paging_sim();
    
    log_result();

    return SUCCESS;
}

/**
 * Uppers the entire string.
 */
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
            file_name = argv[i];
            printf("file_name: %s\n", file_name);
            break;

        case 3:
            page_size = atoi(argv[i]);
            printf("page_size: %lu\n", page_size);
            break;char mode;

        case 4:
            mem_size = atoi(argv[i]);
            printf("mem_size: %lu\n", mem_size);
            break;
        }
    }
}

void configure_sim()
{
    // Tries to open file
    if (!(file = fopen(file_name, "r")))
        error("fopen");
    
    // Number of pages equals the reason between total memory size and page size
    page_num = (mem_size * MB_TO_kB) / page_size;

    // Offset equals the number of bytes needed do describe all positions in a page
    offset = LOG2_kB + (size_t)(ceil(log2(page_size)));
}

void paging_sim()
{
    char            mode;
    int             status;
    unsigned int    addr;

    // while (status != -1)
    // {
    //     time++;
    //     fscanf(file, " %x %c", &addr, &mode);
    // }

}

void log_result()
{
    printf("Arquivo de entrada:                     %s\n", file_name);
    printf("Tamanho da memória física:              %lu MB\n", mem_size);
    printf("Tamanho das páginas:                    %lu kB\n", page_size);
    printf("Offset de bytes:                        %lu\n", offset);
    printf("Número máximo de páginas em memória:    %d\n", page_num);
    printf("Algoritmo de substituição:              %s\n", subs_method);
    printf("Número de Faltas de Página:             %d\n", page_fault_count);
    printf("Número de Páginas Escritas:             %d\n", page_write_count);
}
