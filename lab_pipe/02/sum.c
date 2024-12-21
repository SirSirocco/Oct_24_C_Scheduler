#include <stdio.h>
#include <stdlib.h>

#define error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(void)
{
    int sum, int0, int1;

    scanf(" %d %d", &int0, &int1);

    sum = int0 + int1;
    printf("Sum: %d\n", sum);

    return EXIT_SUCCESS;
}
