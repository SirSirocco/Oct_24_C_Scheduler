#include <stdio.h>
#include <unistd.h>

int main(void)
{
    if (fork())
        printf("Hello World!\n");

    return 0;
}