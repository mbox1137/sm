#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int mode = 0;

void func(int signo)
{
    if (signo == SIGUSR1)
        mode = 1;
    else if (signo == SIGUSR2)
        mode = 2;
    else if (signo == SIGTERM)
        mode = 3;
}

int main(int argc, char *argv[])
{
    int counter1 = 0, counter2 = 0;
    struct sigaction sa = {};
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = func;

    sigaction(SIGUSR1, &sa, 0);
    sigaction(SIGUSR2, &sa, 0);
    sigaction(SIGTERM, &sa, 0);

    sigset_t set, set2;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);
    sigaddset(&set, SIGTERM);

    sigprocmask(SIG_BLOCK, &set, &set2);
    printf("%d\n", getpid());
    fflush(stdout);
//    sigprocmask(SIG_UNBLOCK, &set, NULL);

    while (1)
    {
        while (!mode)
            sigsuspend(&set2);

        if (mode == 1)
        {
            printf("%d %d\n", counter1, counter2);
            fflush(stdout);
            counter1++;
        } else if (mode == 2)
            counter2++;
        else if (mode == 3)
            _exit(0);

        mode = 0;
    }

    exit(EXIT_SUCCESS);
}
