//man pthread_cond_wait
//https://ru.wikipedia.org/wiki/%D0%A3%D1%81%D0%BB%D0%BE%D0%B2%D0%BD%D0%B0%D1%8F_%D0%BF%D0%B5%D1%80%D0%B5%D0%BC%D0%B5%D0%BD%D0%BD%D0%B0%D1%8F

#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/eventfd.h>
#include <unistd.h>

typedef struct
{
    double sum;
    int locked;
} acc_t;

typedef struct Argstag
{
    pthread_mutex_t *pmutex;
    pthread_cond_t *cond;
    acc_t *accs;
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
    int i;

    for(i = 0; i < a->iters; i++)
    {
        pthread_mutex_lock(a->pmutex);
        while(a->accs[a->acc1].locked || a->accs[a->acc2].locked)
        {
            pthread_cond_wait(a->cond, a->pmutex);
        }
        a->accs[a->acc1].locked=1;
        a->accs[a->acc2].locked=1;
        pthread_mutex_unlock(a->pmutex);
        a->accs[a->acc1].sum += a->ds1;
        a->accs[a->acc2].sum += a->ds2;
        a->accs[a->acc1].locked=0;
        a->accs[a->acc2].locked=0;
        pthread_cond_signal(a->cond);
    }

    return(args);
}

int main(int argc, char* argv[])
{
    int k;
    int status;
    Argst *ums;
    acc_t *accs;
    pthread_t *threads;
    pthread_mutex_t mutex;
    pthread_cond_t condition;
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

    accs = (acc_t*)malloc(acc_count * sizeof(acc_t));

    if (accs == NULL)
    {
        perror("malloc accs");
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
    for(k = 0; k < acc_count; k++)
    {
        accs[k].sum=0.0;
        accs[k].locked=0;
    }

    if (pthread_mutex_init(&mutex, NULL) != 0)
        exit(1);

    if(pthread_cond_init(&condition,0) !=0)
        exit(1);

    for(k = 0; k < thr_count; k++)
    {
        ums[k].num = k;
        ums[k].pmutex = &mutex;
        ums[k].cond = &condition;
        ums[k].accs = accs;

        status = pthread_create(&threads[k], NULL, tfun, &ums[k]);

        if (status != 0)
        {
            printf("main error: can't create thread, status = %d\n", status);
            exit(-1);
        }
    }

#if DEBUG
    printf("started...\n");
#endif

    for(k = 0; k < thr_count; k++)
    {
        status = pthread_join(threads[k], &result);

        if (status)
        {
            printf("main error: can't join thread, status = %d\n", status);
            exit(-1);
        }
    }

    for(k = 0; k < acc_count; k++)
        printf("%.10lg\n", accs[k].sum);

    pthread_cond_destroy(&condition);
    pthread_mutex_destroy(&mutex);
    free(accs);
    free(ums);
    free(threads);

    return 0;
}

// https://sodocumentation.net/ru/pthreads
// https://learnc.info/c/pthreads_mutex_introduction.html
