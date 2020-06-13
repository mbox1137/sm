#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/eventfd.h>
#include <unistd.h>
#include <poll.h>
#include <math.h>

/*
typedef struct {
    int   fd;         // file descriptor
    short events;     // requested events
    short revents;    // returned events
    } pollfd_t;
*/

typedef struct
{
    int n;
} Argst;

static pthread_t *threads;
static int nn;
static eventfd_t *evs;

void* tfun(void *args)
{
    int n, k;
    uint64_t x;
    int val;

    n = ((Argst *) args)->n;

#if DEBUG
    printf("n=%d\n",n);
#endif

    if (read(evs[n], &x, sizeof(uint64_t)) != sizeof(uint64_t))
    {
        perror("read(ev,...");
        exit(-1);
    }

    if (scanf("%d", &val) == 1)
    {
        printf("%d %d\n", n, val);
    } else
    {
        for(k = 0; k < nn; k++)
        {
            if (k == n)
                continue;
            pthread_cancel(threads[k]);
        }
        exit(1);
    }

    x = 1;
    if (write(evs[abs(val) % nn], &x, sizeof(uint64_t)) != sizeof(uint64_t))
    {
        perror("write(ev,...");
        exit(-1);
    }
    return(args);
}

int main(int argc, char* argv[])
{
    int status;
    int k;
    void *out_void;
    uint64_t x;
    Argst *args;

    if (argc != 2 || sscanf(argv[1], "%d", &nn) != 1)
    {
        fprintf(stderr, "%s 3 <stdin.txt\n", argv[0]);
        return(1);
    }

    threads = malloc(nn * sizeof(pthread_t));
    if (threads == NULL)
    {
        perror("malloc threads");
        exit(-1);
    }

    args = malloc(nn * sizeof(Argst));
    if (args == NULL)
    {
        perror("malloc args");
        exit(-1);
    }

    evs = malloc(nn * sizeof(eventfd_t));
    if (evs == NULL)
    {
        perror("malloc evs");
        exit(-1);
    }

#if DEBUG
    printf("nn=%d\n", nn);
#endif

    for(k = 0; k < nn; k++)
    {
        args[k].n = k;

        evs[k] = eventfd(0, 0);
        if (evs[k] == -1)
        {
            perror("eventfd");
            exit(-1);
        }

        status = pthread_create(&threads[k], NULL, tfun, &args[k]);

        if (status != 0)
        {
            printf("main error: can't create thread, status = %d\n", status);
            exit(-1);
        }
    }

    x = 1;
    if (write(evs[0], &x, sizeof(uint64_t)) != sizeof(uint64_t))
    {
        perror("initial eventfd write");
        exit(-1);
    }

#if DEBUG
    printf("started...\n", nn);
#endif

    for(k = 0; k < nn; k++)
    {
        status = pthread_join(threads[k], &out_void);

        if (status)
        {
            printf("main error: can't join thread, status = %d\n", status);
            exit(-1);
        }
    }

    for(k = 0; k < nn; k++)
        close(evs[k]);
    free(evs);
    free(threads);
    free(args);

    return 0;
}

// https://sodocumentation.net/ru/pthreads

