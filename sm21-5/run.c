#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <sys/signalfd.h>
#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <unistd.h>
#include "run.h"

static int retval;

char* readpipe(int fd)
{
    int n, nr, k;
    char *buf;
    n=0;
    buf=NULL;
    k=0;
    for(;;)
    {
        if(k>=n)
        {
            if(n==0)
                n=1<<16;
            else
                n<<=1;
            buf=realloc(buf, n);
            if(buf==NULL)
                exit(1);
        }
        nr=read(fd, &buf[k], n-k);
        if(nr<0)
            exit(1);
        else if(nr==0)
            break;
        k+=nr;
    }
    buf[k]=0;
    return(buf);
}

void writepipe(int fd, char* s)
{
    int n, nw, k;
    k=0;
    n=strlen(s)+1;
    while(n>0) {
        nw=write(fd, &s[k], n);
        k+=nw;
        n-=nw;
    }
    return;
}

static void clean_up_child_process(int signal_number)
{
    int status;
    retval=0;
    wait(&status);
         if (WIFEXITED(status))    retval = (WEXITSTATUS(status));
    else if (WIFSIGNALED(status))  retval = (1024+WTERMSIG(status));
    else if (WIFSTOPPED(status))   retval = (1024+WSTOPSIG(status));
    else if (WIFCONTINUED(status)) retval = (1024+SIGCONT);
    return;
}

int run(const char* cmd, 
        const char* input, 
        char** poutput, 
        char** perror, 
        int timeot) {

    struct sigaction sigchld_action;
    retval=0;
    memset(&sigchld_action, 0, sizeof(sigchld_action));
    sigchld_action.sa_handler = &clean_up_child_process;
    sigaction(SIGCHLD, &sigchld_action, NULL);
    *poutput=calloc(1,1);
    *perror=calloc(1,1);
    return(retval);
}
