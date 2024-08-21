#include <stdlib.h>

int main(void)
{
    if (fork())
        printf("Hello World!\n");

    return 0;
}