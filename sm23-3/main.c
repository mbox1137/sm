#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <sched.h>
#include <stdatomic.h>
#include <unistd.h>
#include <limits.h>

#define NN 100
#define NI 1000

struct Item
{
    struct Item *next;
    long long value;
};

typedef struct Item Item;
Item *_Atomic root = NULL;

void* tfun(void *args)
{
    long num = (long) args;
    int i;

    for (i = 0; i < NI; ++i)
    {
        Item *temp = malloc(sizeof(Item));
        if (temp == NULL)
            exit(-1);

        temp->next = atomic_exchange_explicit(&root, temp, memory_order_relaxed);
        temp->value = num + i;

        sched_yield();
    }

    return(args);
}

void print_del_list()
{
    Item *temp;
    while(root)
    {
        temp = root;
        printf("%lld\n", root->value);
        root = root->next;
        free(temp);
    }
}

int main(int argc, char *argv[])
{
    pthread_t *threads;
    int status, i;
    void *result;

    threads = malloc(NN * sizeof(pthread_t));
    if (threads == NULL)
    {
        perror("malloc threads");
        exit(-1);
    }

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);

    for (i = 0; i < NN; ++i)
    {
        status = pthread_create(&threads[i], &attr, tfun, (void *) ((long) i * NI));
        if (status != 0)
        {
            printf("main error: can't create thread, status = %d\n", status);
            exit(-1);
        }
    }


    for (i = 0; i < NN; ++i)
    {
        status = pthread_join(threads[i], &result);
        if (status != 0)
        {
            printf("main error: can't join thread, status = %d\n", status);
            exit(-1);
        }
    }

    print_del_list();

    free(threads);

    return 0;
}
