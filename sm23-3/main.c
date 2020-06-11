#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/eventfd.h>
#include <unistd.h>
#include <sched.h>

#define NN 100
#define NI 1000

struct Item
{
    struct Item *prev;
    struct Item *next;
    long long value;
};

static struct Item *first=NULL;
static struct Item *last=NULL;

typedef struct Argstag
{
    int n;
    pthread_mutex_t *pmutex;
} Argst;

void *tfun(void *args)
{
    Argst *a = args;
    int i;
    struct Item *item;

    for(i = 0; i < NI; i++)
    {
        item=(struct Item*) malloc(sizeof(struct Item));
        if(item==NULL)
            exit(-1);
        item->next=NULL;
        item->value=(a->n)*NI+i;

        pthread_mutex_lock(((Argst*)args)->pmutex);
        if(!first)
        {
            first=item;
            last=item;
        }
        last->next=item;
        item->prev=last;
        last=item;
        pthread_mutex_unlock(((Argst*)args)->pmutex);

        sched_yield();
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
    struct Item *item;

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

    for(item = first; item != NULL; item=item->next)
        printf("%lld\n", item->value);

    for(item = last; item != first; item=item->prev)
        free(item->next);
    free(first);
    return 0;
}

// https://sodocumentation.net/ru/pthreads
// https://learnc.info/c/pthreads_mutex_introduction.html

