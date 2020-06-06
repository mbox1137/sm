#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//pthread_create pthread_join

typedef struct {
    int n;
} args_t;

void* tfun(void *args) {
    pthread_t thread;
    int status;
    int status_addr;
    args_t a;
    a=*((args_t*)args);

    printf("%d\n",a.n);
    a.n++;
    if(a.n>9)
        return(NULL);
    status = pthread_create(&thread, NULL, tfun, &a);
    if (status != 0) {
        printf("main error: can't create thread, status = %d\n", status);
        exit(-11);
    }
 
    status = pthread_join(thread, (void**)&status_addr);
    if (status) {
        printf("main error: can't join thread, status = %d\n", status);
        exit(-12);
    }

    return(NULL);
}

int main(int argc, char** argv) {
    args_t args;
    args.n=0;
    tfun(&args);
    return(0);
}
