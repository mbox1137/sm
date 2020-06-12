//man pthread_cond_wait

#define DEBUG 1

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
    pthread_mutex_t *pmutex;
    int num;
    int iters;
    int acc1;
    double ds1;
    int acc2;
    double ds2;
} Argst;

void* tfun(void *args)
{
    Argst *a = args;
    int i, k;
    k = a->num;

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
    int acc_count, thr_count;

    if(
        (scanf("%d", &acc_count)!=1)
     || (scanf("%d", &thr_count)!=1)
    )
        exit(-1);

    threads = malloc(thr_count * sizeof(pthread_t));

    if (threads == NULL)
    {
        perror("malloc threads");
        exit(-1);
    }

    ums = (Argst*)malloc(thr_count * sizeof(Argst));

    if (ums == NULL)
    {
        perror("malloc args");
        exit(-1);
    }

    for(k = 0; k < thr_count; k++)
        if(scanf("%d%d%lg%d%lg",
                        &ums[k].iters, 
                        &ums[k].acc1, 
                        &ums[k].ds1, 
                        &ums[k].acc2, 
                        &ums[k].ds2) != 5 )
            exit(-1);
#if DEBUG
    printf("acc_count=%d\n", acc_count);
    printf("thr_count=%d\n", thr_count);
    for(k = 0; k < thr_count; k++)
        printf("iters=%d acc1=%d ds1=%lg acc2=%d ds2=%lg\n",
                        ums[k].iters, 
                        ums[k].acc1, 
                        ums[k].ds1, 
                        ums[k].acc2, 
                        ums[k].ds2);
#endif
#if 0
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
#endif
    free(ums);
    free(threads);

//    for(k = 0; k < NN; k++)
//        printf("%.10lg\n", x[k]);

    return 0;
}

// https://sodocumentation.net/ru/pthreads
// https://learnc.info/c/pthreads_mutex_introduction.html

