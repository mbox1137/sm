#define DEBUG 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/signalfd.h>
#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <unistd.h>
#include "run.h"

char* readpipe(int fd)
{
    int n, nr, k;
    char *buf;
    n = 0;
    buf = NULL;
    k = 0;
    for(;;)
    {
        if (k >= n)
        {
            if (n == 0)
                n = 1<<16;
            else
                n <<= 1;

            buf = realloc(buf, n);
            if (buf == NULL)
                exit(1);
        }

        nr = read(fd, &buf[k], n - k);
        if (nr < 0)
            exit(1);
        else if (nr == 0)
            break;
        k += nr;
    }

    buf[k] = 0;

    return(buf);
}

void writepipe(int fd, const char* s)
{
    int n, nw, k;
    k = 0;
    n = strlen(s) + 1;

    while(n > 0)
    {
        nw = write(fd, &s[k], n);
        k += nw;
        n -= nw;
    }

    return;
}

int run(const char* cmd, const char* input, char** poutput, char** perror, int timeout)
{
    int pipein[2], pipeout[2], pipeerr[2];
    pid_t pid;
    int retval;
    int status;
/*
    struct sigaction sigchld_action;
    retval = 0;
    memset(&sigchld_action, 0, sizeof(sigchld_action));
    sigchld_action.sa_handler = &clean_up_child_process;
    sigaction(SIGCHLD, &sigchld_action, NULL);
*/
    if (pipe(pipein) == -1)
        exit(-1);
    if (pipe(pipeout) == -1)
        exit(-1);
    if (pipe(pipeerr) == -1)
        exit(-1);

    pid = fork();

    if (pid == -1)
        exit(-1);

    if (!pid)
    {
#if DEBUG
        printf("child\n");
#endif
        dup2(pipein[0], 0);
        close(pipein[0]);
        close(pipein[1]);

        dup2(pipeout[1], 1);
        close(pipeout[0]);
        close(pipeout[1]);

        dup2(pipeerr[1], 2);
        close(pipeerr[0]);
        close(pipeerr[1]);

        execlp(cmd, cmd, NULL);
        _exit(1);
    }
#if DEBUG
        printf("parent\n");
#endif

    close(pipein[0]);
    close(pipeout[1]);
    close(pipeerr[1]);
    *poutput = NULL;
    *perror = NULL;

    writepipe(pipein[1], input);
    *poutput = readpipe(pipeout[0]);
    *perror = readpipe(pipeerr[0]);
    close(pipein[1]);
    close(pipeout[0]);
    close(pipeerr[0]);

    retval = 0;
    wait(&status);

    if (WIFEXITED(status))
        retval = (WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        retval = (1024 + WTERMSIG(status));
    else if (WIFSTOPPED(status))
        retval = (1024 + WSTOPSIG(status));
    else if (WIFCONTINUED(status))
        retval = (1024 + SIGCONT);

    return(retval);
}

/*
    struct sigaction sigchld_action;
    retval = 0;
    memset(&sigchld_action, 0, sizeof(sigchld_action));
    sigchld_action.sa_handler = &clean_up_child_process;
    sigaction(SIGCHLD, &sigchld_action, NULL);

static void clean_up_child_process(int signal_number)
{
    int status;
    cld=1;
    retval = 0;
    wait(&status);

    if (WIFEXITED(status))
        retval = (WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        retval = (1024 + WTERMSIG(status));
    else if (WIFSTOPPED(status))
        retval = (1024 + WSTOPSIG(status));
    else if (WIFCONTINUED(status))
        retval = (1024 + SIGCONT);

    return;
}
*/
