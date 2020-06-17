#define DEBUG 1
#define LINE 0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/signalfd.h>
#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/time.h>
#include <malloc.h>

#define NN 132

int start (const char* cmd, int *fd);

int getnum(FILE *f) {
    int x;
    char lin[NN];
    x=-1;
    for(;;) {
        if(!fgets(lin,NN,f))
            break;
        if(sscanf(lin,"%d", &x)==1)
            break;
    }
    return(x);
}

int main(int argc, char** argv) {
    char *p1, *p2;
    pid_t pid[2];
    int p1fd[3], p2fd[3];
    FILE *p1stdin, *p1stdout, *p1stderr;
    FILE *p2stdin, *p2stdout, *p2stderr;
    int status;
    int x,y;
    int k;
#if LINE
    char lin[NN];
#endif
    if(argc==3)
    {
        p1=argv[1];
        p2=argv[2];
    } else {
        fprintf(stderr, "%s p1.py p2.py\n", argv[0]);
        return(1);
    }

    pid[0]=start(p1, p1fd);
    pid[1]=start(p2, p2fd);
    p1stdin=fdopen(p1fd[0], "w");
    p1stdout=fdopen(p1fd[1], "r");
    p1stderr=fdopen(p1fd[2], "r");
    p2stdin=fdopen(p2fd[0], "w");
    p2stdout=fdopen(p2fd[1], "r");
    p2stderr=fdopen(p2fd[2], "r");
#if DEBUG    
    sleep(1);
#endif
    while(!feof(stdin))
    {
#if LINE
        if(fgets(lin,NN,stdin)) {
            fputs(lin,p1stdin);
            fflush(p1stdin);
            if(fgets(lin,NN,p1stdout))
            {
                fputs(lin,p2stdin);
                fflush(p2stdin);
                if(fgets(lin,NN,p2stdout))
                {
                    fputs(lin,stdout);
                }
            }
        }
#else
        if(!feof(stdin))
        {
            x=getnum(stdin);
#if DEBUG    
            fprintf(stderr, "x(stdin)=%d\n", x);
#endif
            fprintf(p1stdin, "%d\n", x);
            fflush(p1stdin);
            y=getnum(p1stdout);
            if(!y&1)
            {
                x=y;
                fprintf(p2stdin, "%d\n", x);
                fflush(p2stdin);
                y=getnum(p2stdout);
            }
            printf("%d\n", y);
        }
#endif
    }
    for(k=0; k<3; k++)
    {
        close(p1fd[k]); 
        close(p2fd[k]); 
    }
    fclose(p1stdin);
    fclose(p1stdout);
    fclose(p1stderr);
    fclose(p2stdin);
    fclose(p2stdout);
    fclose(p2stderr);
    
    for(k=0; k<2; k++)
    {
        waitpid(pid[k], &status, 0);
/*
        if (WIFEXITED(status))
            retval = (WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            retval = (1024 + WTERMSIG(status));
        else if (WIFSTOPPED(status))
            retval = (1024 + WSTOPSIG(status));
        else if (WIFCONTINUED(status))
            retval = (1024 + SIGCONT);
*/
    }

    return(0);
}

//-------------------------------------
int start (const char* cmd, int *fd)
{
    int pipein[2], pipeout[2], pipeerr[2];
    pid_t pid;

    if (pipe(pipein) == -1)
    {
        perror("pipein");
        exit(-1);
    }
    if (pipe(pipeout) == -1)
    {
        perror("pipeout");
        exit(-1);
    }
    if (pipe(pipeerr) == -1)
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

    close(pipein[0]);
    close(pipeout[1]);
    close(pipeerr[1]);
    fd[0]=pipein[1];
    fd[1]=pipeout[0];
    fd[2]=pipeerr[0];

    return(pid);
}
