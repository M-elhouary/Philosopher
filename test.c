#include <pthread.h>
#include <stdio.h>

int main()
{
    printf(" size of mutex = %d\n ", sizeof(pthread_mutex_t));
    return 0;
}

