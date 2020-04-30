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
    int k, n;

    if(scanf("%d", &n) != 1)
    {
        perror("sscanf");
        exit(EXIT_FAILURE);
    }

    mypid = getpid();

    if(n > 0)
    {
        printf("%d", 1);
        fflush(NULL);
    }

    for(k = 2; k <= n; k++)
    {
        cpid = fork();
        if (cpid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (cpid == 0)
        {
            printf(" %d", k);
            fflush(NULL);
            continue;
        } else {
            wait(NULL);
            break;
        }
    }

    if(mypid == getpid() && n > 0)
        printf("\n");

    exit(EXIT_SUCCESS);
}

// man 2 pipe
