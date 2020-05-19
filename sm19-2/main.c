#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define MSIG1 (SIGUSR1)
#define MSIG2 (SIGUSR2)

volatile int flag = 0;

void func(int signo)
{
    if (signo == MSIG1)
        flag = 0;
    else if (signo == MSIG2)
        flag = 1;
}

int main(int argc, char *argv[])
{
    int num;
    struct sigaction sa = {};
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = func;

    sigaction(MSIG1, &sa, 0);
    sigaction(MSIG2, &sa, 0);

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, MSIG1);
    sigaddset(&mask, MSIG2);

    sigprocmask(SIG_BLOCK, &mask, 0);
    printf("%d\n", getpid());
    fflush(stdout);
    sigprocmask(SIG_UNBLOCK, &mask, 0);

    while (scanf("%d", &num) == 1)
    {
        if (!flag)
            printf("%d\n", -num);
        else
            printf("%d\n", num * num);

        fflush(stdout);
    }

    exit(EXIT_SUCCESS);
}

// https://github.com/blackav/hse-caos-2019/blob/master/19-signal1/sem-signals.pdf
