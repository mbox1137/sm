#define DEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int counter = 0;

void func(int signo)
{
//    (void)signo;

    if (counter == 4)
        _exit(EXIT_SUCCESS);

    printf("%d\n", counter);
    counter++;

    fflush(stdout);
}


int main(int argc, char *argv[])
{
    int k;

#if DEBUG
    for(k = 1; k < argc; k++)
        printf("%s\n", argv[k]);
#endif
    printf("SIGRTMIN=%d\tSIGRTMAX=%d\n", SIGRTMIN, SIGRTMAX);
    return(0);

//    printf("%d\n", getpid());
//    fflush(stdout);

    struct sigaction sa = {}; // инициализируем нулями
    sa.sa_flags = SA_RESTART; // restartable system calls
    sa.sa_handler = func;     // обработчик сигнала
    sigaction(SIGINT, &sa, 0);

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);

    sigprocmask(SIG_BLOCK, &set, 0);
    printf("%d\n", getpid());
    fflush(stdout);
    sigprocmask(SIG_UNBLOCK, &set, NULL);

    while (1)
        pause();

    exit(EXIT_SUCCESS);
}


/*
struct sigaction
{
    void     (*sa_handler)(int);
    void     (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t   sa_mask;
    int        sa_flags;
    void     (*sa_restorer)(void);
};

int sigaction(int signo, const struct sigaction *act, struct sigaction *oldact);


https://github.com/blackav/hse-caos-2019/blob/master/19-signal1/sem-signals.pdf
*/
