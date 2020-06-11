#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    int n;
    pthread_t last;
} Argst;

void *tfun(void *args)
{
    int status_addr;
    Argst *a;
    a = (Argst *) args;

    if (a->n > 0)
    {
        if (pthread_join(a->last, (void**)&status_addr) != 0)
        {
            printf("main error: can't join thread\n");
            exit(-1);
        }
    }

    printf("%d\n", a->n);

    return(NULL);
}

int main(int argc, char* argv[])
{
    int status;
    pthread_t thread = 0;
    Argst args[10];

    for(int i = 0; i < 10; ++i)
    {
        args[i].n = i;
        args[i].last = thread;

        status = pthread_create(&thread, NULL, tfun, &args[i]);

        if (status != 0)
        {
            printf("main error: can't create thread, status = %d\n", status);
            exit(-1);
        }
    }

    if (pthread_join(thread, NULL) != 0)
    {
        printf("main error: can't join thread, status = %d\n", status);
        exit(-1);
    }

    return 0;
}




