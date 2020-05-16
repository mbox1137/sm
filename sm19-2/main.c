#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int mode = 0;

void func(int signo)
{
    if (signo == SIGUSR1)
        mode = 0;
    else if (signo == SIGUSR2)
        mode = 1;
}

int main(int argc, char *argv[])
{
    struct sigaction sa = {};
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = func;

    sigaction(SIGUSR1, &sa, 0);
    sigaction(SIGUSR2, &sa, 0);

    printf("%d\n", getpid());
    fflush(stdout);

    int num;

    while (scanf("%d", &num) == 1)
    {
        if (!mode)
            printf("%d\n", -num);
        else
            printf("%d\n", num * num);

        fflush(stdout);
    }

    exit(EXIT_SUCCESS);
}
