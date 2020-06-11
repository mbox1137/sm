//man pthread_cond_wait

#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/eventfd.h>
#include <unistd.h>

#define NN 3
#define NI 1000000

static double x[NN];

typedef struct Argstag
{
    int n;
    pthread_mutex_t *pmutex;
} Argst;

void* tfun(void *args)
{
    Argst *a = args;
    int i, k;
    k = a->n;

    for(i = 0; i < NI; i++)
    {
        pthread_mutex_lock(((Argst*)args)->pmutex);
        x[k] += (k + 1) * 100;
        x[(k + 1) % NN] -= (k + 1) * 100 + 1;
        pthread_mutex_unlock(((Argst*)args)->pmutex);
    }

    return(args);
}

int main(int argc, char* argv[])
{
    int k;
    int status;
    Argst *ums;
    pthread_t *threads;
    pthread_mutex_t mutex;
    void* result;

    for(k = 0; k < NN; k++)
        x[k] = 0.0;

    threads = malloc(NN * sizeof(pthread_t));

    if (threads == NULL)
    {
        perror("malloc threads");
        exit(-1);
    }

    ums = malloc(NN * sizeof(Argst));

    if (ums == NULL)
    {
        perror("malloc args");
        exit(-1);
    }

    if (pthread_mutex_init(&mutex, NULL) != 0)
        exit(1);

    for(k = 0; k < NN; k++)
    {
        ums[k].n = k;
        ums[k].pmutex = &mutex;
        status = pthread_create(&threads[k], NULL, tfun, &ums[k]);

        if (status != 0)
        {
            printf("main error: can't create thread, status = %d\n", status);
            exit(-1);
        }
    }

#if DEBUG
    printf("started...\n", NN);
#endif

    for(k = 0; k < NN; k++)
    {
        status = pthread_join(threads[k], &result);

        if (status)
        {
            printf("main error: can't join thread, status = %d\n", status);
            exit(-1);
        }
    }

    pthread_mutex_destroy(&mutex);

    free(ums);
    free(threads);

    for(k = 0; k < NN; k++)
        printf("%.10lg\n", x[k]);

    return 0;
}

// https://sodocumentation.net/ru/pthreads
// https://learnc.info/c/pthreads_mutex_introduction.html

