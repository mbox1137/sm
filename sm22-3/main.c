#define DEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//pthread_create pthread_join

typedef struct {
    int n;
} args_t;

void* tfun(void *args) {
    return(NULL);
}

int main(int argc, char** argv) {
    pthread_t *threads;
    int status;
    int status_addr;

    int k,n;
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
    for(k=0; k<n; k++) {
        status = pthread_join(threads[k], (void**)&status_addr);
        if (status) {
            printf("main error: can't join thread, status = %d\n", status);
            exit(-12);
        }
    }
    printf("%d\n",n);
    free(threads);
    return(0);
}
