#include "sim_virtual.h"
#include "subs_method.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MB_TO_kB    (size_t)pow(2.0, 10.0)
#define LOG2_kB     (size_t)10
#define BUF_SIZ     128
#define TRUE        1
#define FALSE       0
#define SUCCESS     0
#define error(msg)  do { perror(msg); exit(EXIT_FAILURE); } while (0)


#define LRU             "LRU"
#define SECOND_CHANCE   "SC"
#define NRU             "NRU"
#define OPTIMAL         "OTIMO"

#define lru             0
#define sc              1
#define nru             2
#define opt             3

char*   file_name;
char*   subs_method;

FILE*   file;

size_t  mem_size;
size_t  page_size;
size_t  offset;
   
unsigned int    subs_method_case;
unsigned int    page_num_max;
unsigned int    page_fault_count = 0;
unsigned int    page_write_count = 0;
unsigned int    time = 0;

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

// TODO
void get_subs_method_case(void)
{
    if (!strcmp(subs_method, LRU))
        subs_method_case = lru;
    else if (!strcmp(subs_method, SECOND_CHANCE))
        subs_method_case = sc;
    else if (!strcmp(subs_method, NRU))
        subs_method_case = nru;
    else if (!strcmp(subs_method, OPTIMAL))
        subs_method_case = opt;
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
            break;

        case 4:
            mem_size = atoi(argv[i]);
            printf("mem_size: %lu\n", mem_size);
            break;
        }
    }
}

void configure_sim(void)
{
    // Tries to open file
    if (!(file = fopen(file_name, "r")))
        error("fopen");
    
    // Max number of pages equals the reason between total memory size and page size
    page_num_max = (mem_size * MB_TO_kB) / page_size;

    // Offset equals the number of bytes needed do describe all positions in a page
    offset = LOG2_kB + (size_t)(ceil(log2(page_size)));

    // Optimizes subs method access
    get_subs_method_case();
}

Page* page_fault(unsigned int index, char mode, PageList* page_list)
{
    Page* page = NULL;
    PageEntry* page_entry = create_page_entry(index, time, 0, TRUE, FALSE, NULL); // TODO tempo
    page_fault_count++;

    // printf("PAGE ENTRY\n:");
    // print_page_entry(page_entry);

    set_mflag(page_entry, mode);

    if (!has_room(page_list))
    {
        switch (subs_method_case)
        {
            case lru:
                page = lru_subs(page_list);
                break;
            
            case sc:
                page = sc_subs(page_list);
                break;

            case nru:
                page = nru_subs(page_list);
                break;
        }
    }

    switch (subs_method_case)
    {
        case lru:
            lru_add(page_list, page_entry);
            break;

        case sc:
            sc_add(page_list, page_entry);
            break;

        case nru:
            nru_add(page_list, page_entry);
            break;
    }

    return page;
}

void list_update(unsigned int index, char mode, PageList* page_list)
{
    switch (subs_method_case)
    {
        case lru:
            lru_update(index, mode, time, page_list);
            break;
        
        case sc:
            sc_update(index, mode, page_list);
            break;

        case nru:
            nru_update(index, mode, time, page_list);
            break;
    }
}

void page_write(Page** page)
{
    page_write_count++;
    free_page(*page);
    *page = NULL;
}

void paging_sim(void)
{
    char            mode;
    int             last_addr = FALSE;
    unsigned int    addr;
    unsigned int    pg_idx;
    PageList*       pg_lst = create_page_list(4 /*page_num_max*/); // DEBUG
    Page*           pg = NULL;

    // DEBUG
    printf("\n\nsubs_method_case: %d\n\n", subs_method_case);

    while (fscanf(file, " %x %c ", &addr, &mode) != EOF) // Leave blank space in the end for feof to work properly
    {
        printf("\n### TIME %u\n", time);
        // printf("%u\n", addr);

        if (feof(file))
            last_addr = TRUE;

        // Gets page index
        pg_idx = addr >> offset;

        printf("PG_IDX: %d\n", pg_idx);
        
        if (check_page_in_list(pg_idx, pg_lst) == FALSE)
        {
            printf("* pg_fault: PG_IDX: %d\n", pg_idx);
            pg = page_fault(pg_idx, mode, pg_lst);
            printf("? PG_RM: %d\n", get_index(pg));
        }
        else
            list_update(pg_idx, mode, pg_lst);

        if (pg != NULL && check_dirty_page(pg) && !last_addr)
        {
            printf("# pg_write: PG_IDX: %d\n", get_index(pg));
            page_write(&pg);
        }

        if (pg != NULL)
        {
            free_page(pg);
            pg = NULL;
        }

        print_page_list(pg_lst);
        
        time++;
    }

    free_page_list(pg_lst, TRUE);
}

void log_result(void)
{
    printf("Arquivo de entrada:                     %s\n", file_name);
    printf("Tamanho da memória física:              %lu MB\n", mem_size);
    printf("Tamanho das páginas:                    %lu kB\n", page_size);
    printf("Offset de bytes:                        %lu\n", offset);
    printf("Número máximo de páginas em memória:    %d\n", page_num_max);
    printf("Algoritmo de substituição:              %s\n", subs_method);
    printf("Número de Faltas de Página:             %d\n", page_fault_count);
    printf("Número de Páginas Escritas:             %d\n", page_write_count);
}
