#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

void func(int _)
{
    exit(0);
}

int main(int argc, char *argv[])
{
    time_t time;
    long int num, worktime;
    struct timeval cur_time = {};
    struct itimerval itv = {};
    struct sigaction sa = {};
    sa.sa_handler = func;

    if (sigaction(SIGALRM, &sa, NULL) == -1)
        exit(EXIT_FAILURE);

    if (scanf("%ld%ld", &time, &num) != 2)
        exit(EXIT_FAILURE);

    if (gettimeofday(&cur_time, NULL) == -1)
        exit(EXIT_FAILURE);

    worktime = 1000000 * (time - cur_time.tv_sec) + (num / 1000 - cur_time.tv_usec);

#if DEBUG
    printf("cur_time = %ld\n", cur_time.tv_sec);
    printf("worktime = %ld\n", worktime / 1000000);
#endif

    if (worktime < 0)
        exit(0);

    itv.it_value.tv_sec = worktime / 1000000;
    itv.it_value.tv_usec = worktime % 1000000;

    if (setitimer(ITIMER_REAL, &itv, NULL) == -1)
        exit(EXIT_FAILURE);

    pause();

    exit(EXIT_SUCCESS);
}
/*
struct itimerval
{
    struct timeval it_interval;  Interval for periodic timer
    struct timeval it_value;     Time until next expiration
};

struct timeval
{
    time_t      tv_sec;          seconds
    suseconds_t tv_usec;         microseconds
};

https://pubs.opengroup.org/onlinepubs/007908775/xsh/systime.h.html
*/
