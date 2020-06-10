//https://sodocumentation.net/ru/pthreads
//https://learnc.info/c/pthreads_mutex_introduction.html

#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//#include <sched.h>
#include <sys/eventfd.h>
#include <unistd.h>
//#include <sys/select.h>
#include <poll.h>
//pthread_create pthread_join

#define nn 3
#define ni 1000000

static double x[nn];

typedef struct args_tag {
    int n;
    pthread_mutex_t *pmutex;
} args_t;

void* tfun(void *args) {
    args_t *a=args;
    int i, k;
    k=a->n;
    for(i=0; i<ni; i++) {
        pthread_mutex_lock(  (((args_t*)args)->pmutex));
        x[k]+=(k+1)*100;
        x[(k+1)%nn]-=(k+1)*100+1;
        pthread_mutex_unlock((((args_t*)args)->pmutex));
    }
    return(args);
}

int main(int argc, char** argv) {
    int k;
    int status;
    args_t *ums;
    pthread_t *threads;
    pthread_mutex_t mutex;
    void* result;

    for(k=0; k<nn; k++)
        x[k]=0.0;

    threads=malloc(nn*sizeof(pthread_t));
    if(threads==NULL) {
        perror("malloc threads");
        exit(-13);
    }
    ums=malloc(nn*sizeof(args_t));
    if(ums==NULL) {
        perror("malloc args");
        exit(-12);
    }
    pthread_mutex_init(&mutex, NULL);
    for(k=0; k<nn; k++) {
        ums[k].n=k;
        ums[k].pmutex=&mutex;
        status = pthread_create(&threads[k], NULL, tfun, &ums[k]);
        if (status != 0) {
            printf("main error: can't create thread, status = %d\n", status);
            exit(-11);
        }
    }
#if DEBUG
    printf("started...\n",nn);
#endif    
    for(k=0; k<nn; k++) {
        status = pthread_join(threads[k], &result);
        if (status) {
            printf("main error: can't join thread, status = %d\n", status);
            exit(-12);
        }
    }
    pthread_mutex_destroy(&mutex);
    free(ums);
    free(threads);
    for(k=0; k<nn; k++)
        printf("%.10lg\n", x[k]);
    return(0);
}
