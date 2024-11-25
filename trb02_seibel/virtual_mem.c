struct page 
{
    int             referenced_flag;
    int             modified_flag;
    unsigned int    addr;
};

typedef struct page Page;