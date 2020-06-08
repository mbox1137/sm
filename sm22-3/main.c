#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>

typedef struct
{
    long long n;
} Argst;

void* tfun(void *args)
{
    int num;
    long long sum;

    Argst *a;
    a = malloc(sizeof(Argst));

    if (a == NULL)
    {
        perror("malloc");
        exit(-1);
    }

    sum = 0;
    while(scanf("%d", &num) == 1)
    {
        sum += num;
        sched_yield();
    }

    a->n = sum;
    return(a);
}

int main(int argc, char* argv[])
{
    pthread_t *threads;
    int status;
    int k,n;
    long long sum;
    Argst *pa;
    void *out_void;

    if (argc != 2 || sscanf(argv[1], "%d", &n) != 1)
    {
        fprintf(stderr, "%s 3\n", argv[0]);
        return(1);
    }

    threads = malloc(n * sizeof(pthread_t));

    if (threads == NULL)
    {
        perror("malloc");
        exit(-1);
    }

#if DEBUG
    printf("n=%d\n", n);
#endif

    for(k = 0; k < n; k++)
    {
        status = pthread_create(&threads[k], NULL, tfun, NULL);
        if (status != 0)
        {
            printf("main error: can't create thread, status = %d\n", status);
            exit(-1);
        }
    }

    sum = 0;
    for(k = 0; k < n; k++)
    {
        status = pthread_join(threads[k], &out_void);
        if (status)
        {
            printf("main error: can't join thread, status = %d\n", status);
            exit(-1);
        }

        pa = out_void;
        sum += pa->n;
        free(out_void);
    }

    printf("%lld\n", sum);

    free(threads);

    return 0;
}

// https://sodocumentation.net/ru/pthreads

