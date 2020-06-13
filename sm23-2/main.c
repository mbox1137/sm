#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;

uint64_t cur_prime = 0;
volatile int flag = 0;

int if_prime(uint64_t n)
{
    uint64_t i;
    if (n > 1)
    {
        for(i = 2; i * i <= n; ++i)
        {
            if ((n % i) == 0)
                return 0;
        }
        return 1;
    }

    return 0;
}

void* tfun(void *args)
{
    uint64_t *base = args;
    for(;;)
    {
        if (!if_prime(*base))
            *base += 1;
        else
        {
            pthread_mutex_lock(&mutex);
            cur_prime = *base;
            *base += 1;
            flag = 1;
            pthread_cond_signal(&condvar);
            pthread_mutex_unlock(&mutex);
        }
    }
}

int main(int argc, char *argv[])
{
    uint64_t base;
    uint32_t count, i;
    pthread_t thread;
    int status;

    if (scanf("%" SCNu64 "%" SCNu32, &base, &count) != 2)
        exit(-1);

    status = pthread_create(&thread, NULL, tfun, &base);
    if (status != 0)
    {
        printf("main error: can't create thread, status = %d\n", status);
        exit(-1);
    }

    for(i = 0; i < count; ++i)
    {
        pthread_mutex_lock(&mutex);
        if (flag == 0)
            pthread_cond_wait(&condvar, &mutex);
        pthread_mutex_unlock(&mutex);

        printf("%" PRIu64 "\n", cur_prime);
        flag = 0;
    }

    return 0;
}

// https://sodocumentation.net/ru/pthreads
// https://learnc.info/c/pthreads_mutex_introduction.html
// modified https://habr.com/ru/post/205318/
