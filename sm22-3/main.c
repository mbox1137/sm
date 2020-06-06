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

void* tfun(void *args) {
    int sum,num;
    args_t *a;
    a=malloc(sizeof(a));
    if(a==NULL) {
        perror("malloc");
        exit(-14);
    }
    sum=0;
    while(scanf("d", &num)==1) {
        sum+=num;
        sched_yield();
    }
    a->n=sum;
    return(a);
}

int main(int argc, char** argv) {
    pthread_t *threads;
    int status;
    int k,n;
    int sum;
    args_t *pa;
    void *out_void;

    if(argc!=2 || sscanf(argv[1],"%d",&n)!=1) {
        fprintf(stderr,"%s 3\n",argv[0]);
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
    sum=0;
    for(k=0; k<n; k++) {
        status = pthread_join(threads[k], &out_void);
        if (status) {
            printf("main error: can't join thread, status = %d\n", status);
            exit(-12);
        }
        pa=out_void;
        sum+=pa->n;
    }
    printf("%d\n",sum);
    free(threads);
    return(0);
}
