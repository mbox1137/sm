//https://sodocumentation.net/ru/pthreads

#define DEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//#include <sched.h>
#include <sys/eventfd.h>
#include <unistd.h>
//pthread_create pthread_join

typedef struct {
    int n;
} args_t;

static pthread_t *threads;
static int nn;
static eventfd_t ev;

void* tfun(void *args) {
    int n;
    uint64_t x;
    if(((args_t*)args)->n >=0) {
        n=((args_t*)args)->n;
        return(args);
    }
    for(;;) {
        if(read(ev, &x, sizeof(uint64_t)) != sizeof(uint64_t)){
            continue;
        }
        if(n!=nn)
            continue;
        }
    return(args);
}

int main(int argc, char** argv) {
    int status;
    int k,n;
    void *out_void;

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
