#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    int num;
} Argst;

void* tfun(void *args)
{
    pthread_t thread;
    int status;
    int status_addr;
    int n;

    if (scanf("%d", &n) != 1)
        return(NULL);

    status = pthread_create(&thread, NULL, tfun, NULL);

    if (status != 0)
    {
        printf("main error: can't create thread, status = %d\n", status);
        exit(-1);
    }

    status = pthread_join(thread, (void**)&status_addr);

    if (status)
    {
        printf("main error: can't join thread, status = %d\n", status);
        exit(-1);
    }

    printf("%d\n", n);

    return(NULL);
}

int main(int argc, char* argv[])
{
    Argst args;
    tfun(&args);

    return 0;
}
