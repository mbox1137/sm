#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* tfun(void *args)
{
    pthread_t thread;
    int status;
    int n;

    if (scanf("%d", &n) != 1)
        return(NULL);

    status = pthread_create(&thread, NULL, tfun, NULL);

    if (status != 0)
    {
        printf("main error: can't create thread, status = %d\n", status);
        exit(-1);
    }

    status = pthread_join(thread, NULL);

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
    tfun(NULL);

    return 0;
}
