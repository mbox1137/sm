//https://sodocumentation.net/ru/pthreads

#define DEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
//pthread_create pthread_join

typedef struct {
    int n;
} args_t;

static pthread_t *threads;
static int nn;

void* tfun(void *args) {
    int n;
    if(((args_t*)args)->n >=0) {
        n=((args_t*)args)->n;
        return(args);
    }
    if(n!=nn)
        return(args);
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
    return(0);
}
