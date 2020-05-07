#define DEBUG 1

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
    pid_t child = fork();

    if (child < 0)
        return -1;

    if (child)
    {
        waitpid(child, &wstatus, 0);

        if (WIFSIGNALED(wstatus))
            return 128 + WTERMSIG(wstatus);
        else
            return WEXITSTATUS(wstatus);
    } else {
        execlp("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    }
}

// man waitpid
