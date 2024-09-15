#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    fprintf(stdout, "Indo dormir...\n");
    sleep(5);
    fprintf(stdout, "Acordei!\n");
    exit(EXIT_SUCCESS);
}
