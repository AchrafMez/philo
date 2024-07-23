#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

void* even(void *arg)
{
    int i = 1;
    while(i <= 20)
    {
        printf("even number: %d\n", i);
        usleep(300000);
        i += 2;
    }
    return NULL;
}

void* odd(void *arg)
{
    int i = 0;
    while(i <= 10)
    {
        printf("odd number: %d\n", i);
        usleep(300000);
        i += 2;
    }
    return NULL;
}

int main(){
    pthread_t thread;

    pthread_create(&thread, NULL, &even, NULL);
    odd(NULL);
    pthread_join(thread, NULL);
}