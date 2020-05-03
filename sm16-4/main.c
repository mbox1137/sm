#define DEBUG 0

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>

int main(int argc, char *argv[])
{
    pid_t cpid, mypid;
    int n;
    int exitstatus;
    int pstat;

    if (argc != 1)
    {
        fprintf(stderr, "Usage: %s <main.tst\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    mypid = getpid();
    while(1)
    {
        if(scanf("%d", &n) != 1)
            exit(EXIT_SUCCESS);
        cpid = fork();
#if DEBUG
        if ((cpid == -1) || (n == -1))
        {
#else
        if (cpid == -1)
        {
#endif
            exit(EXIT_FAILURE);
        }
        if (cpid == 0)
            continue;
        else
        {
            waitpid(cpid, &pstat, 0);
            if (WIFEXITED(pstat))
            {
                exitstatus = WEXITSTATUS(pstat);
                if (exitstatus)
                {
                    if (mypid==getpid())
                    {
                        printf("-1\n");
                        exit(EXIT_SUCCESS);
                    }
                    exit(EXIT_FAILURE);
                }
            }
            printf("%d\n", n);
            break;
        }
    }
    exit(EXIT_SUCCESS);
}

// man 2 pipe
