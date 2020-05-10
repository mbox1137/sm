#define DEBUG 0

//#include "mysys.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int mysys(const char *str)
{
    int wstatus;
#if DEBUG
    fprintf(stderr,"cmd=\"%s\"\n", str);
#endif
    pid_t proc = fork();

    if (proc < 0)
        return -1;

    if (!proc)
    {
        execlp("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    }

    waitpid(proc, &wstatus, 0);

    if (WIFEXITED(wstatus))
        return WEXITSTATUS(wstatus);

    else if (WIFSIGNALED(wstatus))
        return 128 + WTERMSIG(wstatus);

    return WEXITSTATUS(wstatus);
}

// man waitpid
