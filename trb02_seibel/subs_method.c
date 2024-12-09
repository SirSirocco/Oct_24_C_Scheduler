#include "subs_method.h"
#include <stdio.h>

#define TRUE    1
#define FALSE   0

void lru_add(PageList* page_list, PageEntry* page_entry)
{
    printf("LRU ADD\n");
    add_page_list_last(page_entry, page_list);

    // print_page_list(page_list);
}

Page* lru_subs(PageList* page_list)
{
    printf("LRU SUBS\n");
    PageEntry* page_entry = remove_page_list_first(page_list);
    Page* page = get_page(page_entry);

    free_page_entry(page_entry, FALSE);

    return page;
}

void lru_update(int index, char mode, unsigned int time, PageList* page_list)
{
    printf("LRU UPDATE\n");
    PageEntry* page_entry = remove_page_list_index(index, page_list);

    // Page update
    set_last_ref(page_entry, time);
    set_mflag(page_entry, mode);

    add_page_list_last(page_entry, page_list);
}

void sc_add(PageList* page_list, PageEntry* page_entry)
{
    add_page_list_last(page_entry, page_list);
}

Page* sc_subs(PageList* page_list)
{
    return NULL;
}

void sc_update(void)
{
}

