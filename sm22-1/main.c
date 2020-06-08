#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    int n;
} Argst;

void *tfun(void *args)
{
    pthread_t thread;
    int status;
    int status_addr;
    Argst a;
    a = *((Argst*)args);

    printf("%d\n",a.n);
    a.n++;

    if (a.n > 9)
        return(NULL);

    status = pthread_create(&thread, NULL, tfun, &a);

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

    return(NULL);
}

int main(int argc, char* argv[])
{
    Argst args;
    args.n = 0;
    tfun(&args);

    return 0;
}
