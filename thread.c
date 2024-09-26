#include <stdio.h>
#include <pthread.h>

#define NUM_THREAD 5

void* PrintHello(void* threadid)
{
    printf("%d - Hello World\n", (int)threadid);
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t thread[NUM_THREAD];

    for (int t = 0; t < NUM_THREAD; t++)
    {
        printf("Creating thread %d\n", t);
        pthread_create(thread + t, NULL, PrintHello, (void*)t);
    }

    for (int i = 0; i < NUM_THREAD; i++) // Wait for all threads to terminate
        pthread_join(thread[i], NULL);

    return 0;
}
