#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <inttypes.h>

#define MAXUSEC 100000

volatile size_t counter = 0;
volatile uint32_t cur_prime = 0;

int if_prime(uint32_t n)
{
    uint32_t i;
    if (n > 1)
    {
        if (n == 2)
            return 1;

        for(i = 3; i * i <= n; i += 2)
        {
            if ((n % i) == 0)
                return 0;
        }
        return (n % 2);
    }

    return 0;
}

void func(int _)
{
    counter++;
    printf("%" PRIu32 "\n", cur_prime);
    fflush(stdout);

    if (counter == 8)
        exit(0);
}

int main(int argc, char *argv[])
{
    uint32_t low, high;
    struct itimerval itv = {};
    struct sigaction sa = {};
    sa.sa_handler = func;

    if (sigaction(SIGVTALRM, &sa, NULL) == -1)
        exit(EXIT_FAILURE);

    if (scanf("%" SCNu32 "%" SCNu32, &low, &high) != 2)
        exit(EXIT_FAILURE);

    itv.it_value.tv_usec = MAXUSEC;
    itv.it_interval.tv_usec = MAXUSEC;

    if (setitimer(ITIMER_VIRTUAL, &itv, NULL) == -1)
        exit(EXIT_FAILURE);

    for(uint32_t i = low; i < high; ++i)
    {
        if (if_prime(i))
            cur_prime = i;
    }

    if (counter < 8)
    {
        printf("-1\n");
        fflush(stdout);
    }

    exit(EXIT_SUCCESS);
}
