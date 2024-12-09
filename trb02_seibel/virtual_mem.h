#include <stdlib.h>

typedef struct flag_table   FlagTable;
typedef struct page         Page;
typedef struct page_list    PageList;
typedef struct node         PageEntry;

/**
 * Creates new page based on the parameters.
 * 
 * @param index Page's index.
 * @param last_ref Last time in which the page was referenced.
 * @param next_ref Next line of code in which the page will be referenced.
 * @param fr Flag that indicates whether the page has been referenced recently.
 * @param fm Flag that indicates whether the page has been modified recently (written).
 * 
 * @return Pointer to the created page.
 */
Page* create_page(unsigned int index, unsigned int last_ref, unsigned int next_ref, int fr, int fm);

/**
 * Prints all the information regarding the page.
 * If page is NULL, the function simply ignores it.
 */
void print_page(Page* page);

/**
 * Frees all resources allocated by page.
 */
void free_page(Page* page);

/**
 * Creates a new page entry (node) passing page and next as parameters.
 * Does not allocate memory for page and next.
 * 
 * @param page Pointer to the page to be stored in the entry.
 * @param next Next page entry (node).
 * 
 * @return Pointer to the created page entry (node).
 */
PageEntry* create_node(Page* page, PageEntry* next);

/**
 * Wrapper for create_page followed by create_node.
 */
PageEntry* create_page_entry(unsigned int index, unsigned int last_ref, unsigned int next_ref, int fr, int fm, PageEntry* next);

/**
 * Prints all the information regarding the page stored in the entry,
 * the entry's pointer value, and the its next's pointer value.
 * If pg_entry is NULL, the function simply ignores it.
 */
void print_page_entry(PageEntry* page_entry);

/**
 * Frees all allocated resources related to the page entry
 * and also the ones allocated by its page if free_pg == TRUE (1).
 * 
 * @param pg_entry Pointer to the page entry to be freed.
 * @param free_pg If TRUE (== 1), frees page as well.
 */
void free_page_entry(PageEntry* page_entry, int free_pg);

/**
 * Creates new page list. Simultes principal memory's frames.
 * Limits the number of page entries to entry_max.
 * 
 * @param entry_max Max number of entries in the table.
 */
PageList* create_page_list(unsigned int entry_max);

/**
 * Prints the page list's attributes and its entries
 * using print_page_entry.
 */
void print_page_list(PageList* page_list);

/**
 * Frees the page list and all page entries with free_page_entry
 * according to the free_pg flag.
 * 
 * @param pg_list Pointer to the page entry to be freed.
 * @param free_pg If TRUE (== 1), frees pages as well.
 */
void free_page_list(PageList* page_list, int free_pg);

/**
 * @return TRUE (== 1) if entry_num < entry_max, else FALSE (== 0).
 */
int has_room(PageList* page_list);

/**
 * Adds page_entry as the first element of page_list. If page_list was
 * empty, page_entry will be first and last simultaneously.
 */
void add_page_list_first(PageEntry* page_entry, PageList* page_list);

/**
 * Adds page_entry as the last element of page_list. If page_list was
 * empty, page_entry will be first and last simultaneously.
 * Makes page_entry->next to be NULL.
 */
void add_page_list_last(PageEntry* page_entry, PageList* page_list);

/**
 * Adds page_entry according to the order providaded by the compare function cmp.
 * 
 * @param cmp This function should return
 * 
 * a negative value,    if p1 < p2;
 * 0,                   if p1 == p2; or 
 * a positive value,    if p1 > p2.
 */
void add_page_list_ord(PageEntry* page_entry, PageList* page_list, int(*cmp)(Page* p1, Page* p2));

/**
 * Removes first page entry from list and returns a pointer to it.
 * 
 * @return NULL if empty list, else pointer to previous first page entry.
 */
PageEntry* remove_page_list_first(PageList* page_list);

/**
 * Removes last page entry from list and returns a pointer to it.
 * 
 * @return NULL if empty list, else pointer to previous last page entry.
 */
PageEntry* remove_page_list_last(PageList* page_list);

/**
 * Removes from list page entry which contains the page with index and
 * returns a pointer to it.
 * 
 * @return NULL if not found, else pointer to page entry.
 */
PageEntry* remove_page_list_index(unsigned int index, PageList* page_list);

/**
 * Searches for a page entry with index.
 * 
 * @param index The index searched.
 * @param page_list The list of page entries in which to search.
 * 
 * @return NULL if not found, else the pointer to the page entry.
 */
PageEntry* search_page_list(unsigned int index, PageList* page_list);

/**
 * @return
 * 
 * a negative value,    if p1->index < p2->index;
 * 0,                   if p1->index == p2->index; or 
 * a positive value,    if p1->index > p2->index.
 */
int cmp_index(Page* p1, Page* p2);

// FUNCTIONS FOR SIMULATION

/**
 * Returns whether the page with the index passed as argument is
 * in page_list.
 * 
 * @return TRUE (1) if it is, else FALSE (0).
 */
int check_page_in_list(unsigned int index, PageList* page_list);

/**
 * Returns whether the page has been modified (becomes 'dirty').
 * 
 * @return TRUE (1) if it is, else FALSE (0).
 */
int check_dirty_page(Page* page);

int get_index(Page* page);

Page* get_page(PageEntry* page_entry);

void set_last_ref(PageEntry* page_entry, unsigned int time);

void set_mflag(PageEntry* page_entry, char mode);

