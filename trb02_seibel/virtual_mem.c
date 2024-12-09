#include "virtual_mem.h"
#include <stdio.h>
#include <stdlib.h>

#define error(msg)  do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define TRUE        1
#define FALSE       0

// STRUCTS
struct node
{
    Page*       page;
    PageEntry*  next;   
};

struct flag_table
{
    int referenced;
    int modified;
};

struct page 
{
    unsigned int    index;      // Page's index
    unsigned int    last_ref;   // Last time in which the page was referenced.
    unsigned int    next_ref;   // Next line of code in which the page will be referenced.
    FlagTable       flag;
};

struct page_list
{
    unsigned int    entry_num;  // Current number of entries.
    unsigned int    entry_max;  // Max number of entries.
    PageEntry*      first;      // First entry.
    PageEntry*      last;       // Last entry.
};

// FUNCTIONS

Page* create_page(unsigned int index, unsigned int last_ref, unsigned int next_ref, int fr, int fm)
{
    Page* page = (Page*)malloc(sizeof(Page));

    if (page == NULL) // Unable to allocate memory
        error("create_page");

    page->index = index;
    page->last_ref = last_ref;
    page->next_ref = next_ref;
    page->flag.referenced = fr;
    page->flag.modified = fm;

    return page;
}

void print_page(Page* page)
{
    if (page == NULL)
        return;

    printf("Index:          %X\n", page->index);
    printf("Last reference: %u\n", page->last_ref);
    printf("Next reference: %u\n", page->next_ref);
    printf("Flag R:         %d\n", page->flag.referenced);
    printf("Flag M:         %d\n", page->flag.modified);
}

void free_page(Page* page)
{
    free(page);
}

PageEntry* create_node(Page* page, PageEntry* next)
{
    PageEntry* node = (PageEntry*)malloc(sizeof(PageEntry));

    if (node == NULL) // Unable to allocate memory
        error("create_node");

    node->page = page;
    node->next = next;

    return node;
}

void print_page_entry(PageEntry* page_entry)
{
    if (page_entry == NULL) // NULL page entry
        return;
    
    print_page(page_entry->page);
    printf("Current:    %p\n", page_entry);
    printf("Next:       %p\n", page_entry->next);
}

void free_page_entry(PageEntry* page_entry, int free_pg)
{
    if (free_pg == TRUE)
        free_page(page_entry->page);

    free(page_entry);
}

PageEntry* create_page_entry(unsigned int index, unsigned int last_ref, unsigned int next_ref, int fr, int fm, PageEntry* next)
{
    Page* page = create_page(index, last_ref, next_ref, fr, fm);
    return create_node(page, next);
}

PageList* create_page_list(unsigned int entry_max)
{
    PageList* page_list = (PageList*)malloc(sizeof(PageList));

    if (page_list == NULL) // Unable to allocate memory
        error("create_page_list");
    
    // Sets max number of elements
    page_list->entry_max = entry_max;

    // List begins empty
    page_list->entry_num = 0;
    page_list->first = page_list->last = NULL;

    return page_list;
}

void print_page_list(PageList* page_list)
{
    PageEntry* aux = page_list->first;

    printf("Entry count:    %u\n", page_list->entry_num);
    printf("Entry max:      %u\n", page_list->entry_max);
    printf("First element:  %p\n", page_list->first);
    printf("Last element:   %p\n", page_list->last);
    printf("Elements:\n\n");
    while (aux != NULL)
    {
        print_page_entry(aux);
        printf("\n");
        aux = aux->next;
    }
}

void free_page_list(PageList* page_list, int free_pg)
{
    PageEntry* aux;

    while (page_list->first != NULL)
    {
        aux = page_list->first;
        page_list->first = page_list->first->next;
        free_page_entry(aux, free_pg);
    }

    free(page_list);
}

int has_room(PageList* page_list)
{
    return (page_list->entry_num < page_list->entry_max) ? TRUE : FALSE;
}

void add_page_list_first(PageEntry* page_entry, PageList* page_list)
{
    page_list->entry_num++;

    page_entry->next = page_list->first;

    if (page_list->first == NULL)       // Empty list
        page_list->last = page_entry;   // First will also be last

    page_list->first = page_entry;
}

void add_page_list_last(PageEntry* page_entry, PageList* page_list)
{
    page_list->entry_num++;

    page_entry->next = NULL;                // Last element has no next

    if (page_list->last == NULL)            // Empty list
        page_list->first = page_entry;      // First will also be last
    else
        page_list->last->next = page_entry; // Links to previous last

    page_list->last = page_entry;
}

void add_page_list_ord(PageEntry* page_entry, PageList* page_list, int(*cmp)(Page* p1, Page* p2))
{
    PageEntry* aux = page_list->first;
    page_list->entry_num++;

    if (aux == NULL) // Empty list
    {
        page_entry->next = NULL;
        page_list->first = page_list->last = page_entry; // First will also be last
        return;
    }

    if (cmp(page_entry->page, aux->page) < 0) // Add before first
    {
        page_entry->next = aux;
        page_list->first = page_entry;
        return;
    }

    while (aux->next != NULL && cmp(page_entry->page, aux->next->page) > 0) // Add after first
        aux = aux->next;

    page_entry->next = aux->next;
    aux->next = page_entry;
}

PageEntry* remove_page_list_first(PageList* page_list)
{
    PageEntry* aux;

    aux = page_list->first;

    if (aux == NULL) // Empty list
        return aux;

    page_list->entry_num--;

    if (aux == page_list->last) // Last element
        page_list->first = page_list->last = NULL;
    else
        page_list->first = page_list->first->next;

    aux->next = NULL; // Unlinks

    return aux;
}

PageEntry* remove_page_list_last(PageList* page_list)
{
   PageEntry *aux1 = page_list->last, *aux2;

    if (aux1 == NULL) // Empty list
        return aux1;

    page_list->entry_num--;

    if (aux1 == page_list->first) // Last element
        page_list->first = page_list->last = NULL;
    else
    {
        aux2 = page_list->first;

        // Finds previous of last element
        while (aux2->next != page_list->last)
            aux2 = aux2->next;
        
        page_list->last = aux2;         // Previous is new last
        page_list->last->next = NULL;   // New last has no next
    }

    aux1->next = NULL; // Unlinks

    return aux1;
}

PageEntry* remove_page_list_index(unsigned int index, PageList* page_list)
{
    PageEntry *aux1 = page_list->first, *aux2;
    
    if (aux1 == NULL) // Empty list
        return NULL;

    if (aux1->page->index == index) // Removes first element
    {
        page_list->entry_num--;

        if (aux1 == page_list->last) // Last element
            page_list->last = NULL;
        
        page_list->first = page_list->first->next;

        aux1->next = NULL; // Unlinks
        
        return aux1;
    }

    // Tries to find it after the first
    while (aux1->next != NULL && aux1->next->page->index != index)
        aux1 = aux1->next;

    if (aux1->next == NULL) // Not found
        return NULL;

    page_list->entry_num--;

    aux2 = aux1->next;
    aux1->next = aux1->next->next;

    // Removes last
    if (aux2 == page_list->last)
        page_list->last = aux1->next; // Updates last

    aux2->next = NULL; // Unlinks
    
    return aux2;
}

PageEntry* search_page_list(unsigned int index, PageList* page_list)
{
    PageEntry* aux;

    aux = page_list->first;

    while (aux != NULL && aux->page->index != index)
        aux = aux->next;

    return aux;
}

int cmp_index(Page* p1, Page* p2)
{
    if (p1->index < p2->index)
        return -1;
    
    else if (p1->index == p2->index)
        return 0;
    
    else
        return 1;
}

// FUNCTIONS FOR SIMULATION
int check_page_in_list(unsigned int index, PageList* page_list)
{
    return (search_page_list(index, page_list) == NULL) ? FALSE : TRUE;
}

int check_dirty_page(Page* page)
{
    return page->flag.modified;
}


// FUNCTIONS FOR SUBS METHODS
Page* get_page(PageEntry* page_entry)
{
    if (page_entry == NULL)
        return NULL;
    return page_entry->page;
}

void set_last_ref(PageEntry* page_entry, unsigned int time)
{
    if (page_entry == NULL)
        return;
    
    page_entry->page->last_ref = time;
}

void set_mflag(PageEntry* page_entry, char mode)
{
    if (page_entry == NULL)
        return;
    
    if (mode == 'W')
        page_entry->page->flag.modified = TRUE;
}
