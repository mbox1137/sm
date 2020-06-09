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

typedef struct use_mutex_tag {
    pthread_mutex_t mutex;
} use_mutex_t;

void* tfun(void *args) {
    pthread_mutex_lock(  &(((use_mutex_t*)args)->mutex));
    pthread_mutex_unlock(&(((use_mutex_t*)args)->mutex));
    return(args);
}

int main(int argc, char** argv) {
    int k, nn;
    int status;
    use_mutex_t um;
    pthread_t thread;

    status=pthread_mutex_init(&(um.mutex), NULL);
    if(argc!=2 || sscanf(argv[1],"%d",&nn)!=1) {
        fprintf(stderr,"%s 3 <stdin.txt\n",argv[0]);
        return(1);
    }

    for(k=0; k<nn; k++) {
        status = pthread_create(&thread, NULL, tfun, &um);
        if (status != 0) {
            printf("main error: can't create thread, status = %d\n", status);
            exit(-11);
        }
    }
#if DEBUG
    printf("started...\n",nn);
#endif    
    pthread_mutex_destroy(&(um.mutex));
    return(0);
}
