// #define _GNU_SOURCE
#define DEBUG 0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/signalfd.h>
#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
//#include "run.h"


int run(const char* cmd, const char* input, char** poutput, char** perror, int timeout);
char* readpipe(int fd);
void writepipe(int fd, const char* s, int n);

static pid_t pid;

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
            {
                perror("readpipe");
                exit(-1);
            }
        }

        nr = read(fd, &buf[k], n - k);
        if (nr < 0)
        {
                perror("readpipe, read");
                break;
        }
        else if (nr == 0)
            break;
        k += nr;
    }

    buf[k] = 0;

    return(buf);
}

void writepipe(int fd, const char* s, int n)
{
    int nw, k;
    k = 0;

#if DEBUG
    printf("writepipe: %s\n",s);
#endif

    while(n > 0)
    {
        nw = write(fd, &s[k], n);
        if (nw < 0)
        {
                perror("writepipe, write");
                break;
        }
        else if (nw == 0)
            break;
        k += nw;
        n -= nw;
    }

    return;
}

static void myalarm(int signal_number)
{
    int sig;
    sig = SIGKILL;

#if DEBUG
        fprintf(stderr, "sig(%d): %d -> %d\n", sig, getpid(), pid);
#endif

    kill(pid, sig);
    return;
}

int malarm(int msec)
{
    double s;
    time_t sec;
    suseconds_t usec;
    struct itimerval timer;

    s = msec/1000.0;
    sec = s;
    usec = (s - sec) * 1E6;
    timer.it_value.tv_sec = sec;
    timer.it_value.tv_usec = usec;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &timer, NULL))
    {
        perror("setitimer");
        exit(-1);
    }

    return((int)(s*1000));
}

int run(const char* cmd, const char* input, char** poutput, char** perr, int timeout)
{
    int pipein[2], pipeout[2], pipeerr[2];
    int retval;
    int status;
    struct sigaction sa;

    if (pipe2(pipein, O_CLOEXEC) == -1)
    {
        perror("pipein");
        exit(-1);
    }
    if (pipe2(pipeout, O_CLOEXEC) == -1)
    {
        perror("pipeout");
        exit(-1);
    }
    if (pipe2(pipeerr, O_CLOEXEC) == -1)
    {
        perror("pipeerr");
        exit(-1);
    }

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(-1);
    }

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
        perror("execlp");
        _exit(1);
    }
#if DEBUG
        printf("parent\n");
#endif
    if(timeout > 0)
    {
        memset(&sa, 0, sizeof(sa));
        sa.sa_handler = &myalarm;
        sigaction(SIGALRM, &sa, NULL);
        malarm(timeout);
    }

    close(pipein[0]);
    close(pipeout[1]);
    close(pipeerr[1]);
    *poutput = NULL;
    *perr = NULL;

    writepipe(pipein[1], input, strlen(input));
    close(pipein[1]);
    *poutput = readpipe(pipeout[0]);
    close(pipeout[0]);
    *perr = readpipe(pipeerr[0]);
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

// https://www.informit.com/articles/article.aspx?p=23618&seqNum=14
