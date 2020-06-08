//https://sodocumentation.net/ru/pthreads

#define DEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//#include <sched.h>
#include <sys/eventfd.h>
#include <unistd.h>
//#include <sys/select.h>
#include <poll.h>
//pthread_create pthread_join
/*
typedef struct {
    int   fd;         // file descriptor
    short events;     // requested events
    short revents;    // returned events
    } pollfd_t;
*/
typedef struct {
    int n;
} args_t;

static pthread_t *threads;
static int nn;
static eventfd_t ev;

void* tfun(void *args) {
    int n;
    uint64_t x;
    struct pollfd fds[1];
    int nse;

    if(((args_t*)args)->n >=0) {
        n=((args_t*)args)->n;
        return(args);
    }
    for(;;) {
        fds[0].fd=ev;
        fds[0].events=POLLIN;
        fds[0].revents=0;
        nse=poll(fds, 1, 999);	//999 mS
        if(nse<0) {
            perror("poll");
            exit(-15);
            } else if(nse==0) {
                continue;
            } else if(fds[0].revents == POLLIN) {
                if(n!=nn)
                    continue;
                if(read(ev, &x, sizeof(uint64_t)) != sizeof(uint64_t)){
                    perror("read(ev,...");
                    exit(-17);
                }
/*
*/
                if(write(ev, &x, sizeof(uint64_t)) != sizeof(uint64_t)){
                    perror("write(ev,...");
                    exit(-18);
                }
            }
        }
    return(args);
}

int main(int argc, char** argv) {
    int status;
    int k,n;
    void *out_void;
    uint64_t x;

    if(argc!=2 || sscanf(argv[1],"%d",&n)!=1) {
        fprintf(stderr,"%s 3 <stdin.txt\n",argv[0]);
        return(1);
    }
    threads=malloc(n*sizeof(pthread_t));
    if(threads==NULL) {
        perror("malloc");
        exit(-13);
    }
#if DEBUG
    printf("n=%d\n",n);
#endif    
    ev=eventfd(0, 0);
    nn=0;
    x=1;
    if(write(ev, &x, sizeof(uint64_t)) != sizeof(uint64_t)){
        perror("initial eventfd write");
        exit(-14);
    }
    for(k=0; k<n; k++) {
        status = pthread_create(&threads[k], NULL, tfun, NULL);
        if (status != 0) {
            printf("main error: can't create thread, status = %d\n", status);
            exit(-11);
        }
    }
    for(k=0; k<n; k++) {
        status = pthread_join(threads[k], &out_void);
        if (status) {
            printf("main error: can't join thread, status = %d\n", status);
            exit(-12);
        }
    }
    free(threads);
    close(ev);
    return(0);
}
