#define DEBUG 0

#include "mysys.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int mysys(const char *str)
{
    int wstatus;
#if DEBUG
    fprintf(stderr,"cmd=\"%s\"\n",str);
#endif
    pid_t pros = fork();

    if (pros < 0)
        return -1;

    if (!pros)
    {
        execlp("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    }

    waitpid(pros, &wstatus, 0);

    if (WIFSIGNALED(wstatus))
        return 128 + WTERMSIG(wstatus);

    return WEXITSTATUS(wstatus);
}

// man waitpid
