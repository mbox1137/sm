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
static int ncur, nn;
static eventfd_t ev;

void* tfun(void *args)
{
    int n, k;
    uint64_t x;
    struct pollfd fds[1];
    int nse;
    int val;

    n = ((Argst *) args)->n;

#if DEBUG
    printf("n=%d\n",n);
#endif

    while(1)
    {
        fds[0].fd = ev;
        fds[0].events = POLLIN;
        fds[0].revents = 0;
        nse = poll(fds, 1, 10); // 10 ms

        if (nse < 0)
        {
            perror("poll");
            exit(-1);
        } else if (nse == 0)
            continue;
        else if (fds[0].revents == POLLIN)
        {
            if (n != ncur)
                continue;

            if (read(ev, &x, sizeof(uint64_t)) != sizeof(uint64_t))
            {
                perror("read(ev,...");
                exit(-1);
            }

            if (scanf("%d", &val) == 1)
            {
                printf("%d %d\n", n, val);
                ncur = abs(val) % nn;
            } else
                break;

            x = 1;

            if (write(ev, &x, sizeof(uint64_t)) != sizeof(uint64_t))
            {
                perror("write(ev,...");
                exit(-1);
            }
        }
    }

    for(k = 0; k < nn; k++)
    {
        if (k == ncur)
            continue;

        pthread_cancel(threads[k]);
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

#if DEBUG
    printf("nn=%d\n", nn);
#endif

    ev = eventfd(0, 0);
    if (ev == -1)
    {
        perror("eventfd");
        exit(-1);
    }
    ncur = 0;
    x = 1;

    if (write(ev, &x, sizeof(uint64_t)) != sizeof(uint64_t))
    {
        perror("initial eventfd write");
        exit(-1);
    }

    for(k = 0; k < nn; k++)
    {
        args[k].n = k;

        status = pthread_create(&threads[k], NULL, tfun, &args[k]);

        if (status != 0)
        {
            printf("main error: can't create thread, status = %d\n", status);
            exit(-1);
        }
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

    free(threads);
    free(args);

    close(ev);

    return 0;
}

// https://sodocumentation.net/ru/pthreads

