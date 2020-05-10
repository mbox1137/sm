#define DEBUG 0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include "addname.h"
#include "solution.h"

int runItem(int *lp, int *rp, char* cmd) {
    pid_t pid;
    pid = fork();
    if (pid < 0)
        return(-1);
    if (!pid)
    {
        if(lp[0]) {
            dup2(lp[0], 0);
            close(lp[0]);
            lp[0]=0;
        }
        if(lp[1]) {
            close(lp[1]);
            lp[1]=0;
        }
        if(rp[1]) {
            dup2(rp[1], 1);
            close(rp[1]);
            rp[1]=0;
        }
        execlp(cmd, cmd, NULL);
        exit(EXIT_FAILURE);
    } else {
        if(lp[0]) {
            close(lp[0]);
            lp[0]=0;
        }
        if(lp[1]) {
            close(lp[1]);
            lp[1]=0;
        }
        if(rp[1]) {
            close(rp[1]);
            rp[1]=0;
        }
        return(pid);
    }
}

int solution (int argc, char *argv[]) {
    pid_t *pids;
    int k;
    int status;
    int lp[2], rp[2];
#if DEBUG
    for (k = 0; k<argc; k++) {
        printf("argv[%d]=\t\"%s\"\n", k, argv[k]);
    }
#endif
    if(argc<1)
        return(0);
    pids=malloc(argc*sizeof(pid_t));
    if(argc>1) {
        lp[0]=0;
        lp[1]=0;
        for (k = 0; k<argc-1; k++) {
            pipe(rp);
            pids[k]=runItem(lp, rp, argv[k]);
            lp[0]=rp[0];
            lp[1]=rp[1];
        }
        lp[0]=rp[0];
        lp[1]=rp[1];
        rp[0]=0;
        rp[1]=0; 
        pids[k]=runItem(lp, rp, argv[k]);
    } else {
        k=0;
        lp[0]=0;
        lp[1]=0;
        rp[0]=0;
        rp[1]=0; 
        pids[k]=runItem(lp, rp, argv[k]);
    }
    for (k = 0; k<argc; k++) {
#if DEBUG
        printf("Waiting for %d (%d)\n", k, pids[k]);
#endif
        waitpid(pids[k], &status, 0);
        if (WIFEXITED(status))
            continue;
    }
    free(pids);
    return(0);
}


/*			sm17-1 (prog.c)
#define DEBUG 0

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *cmd;
    int outfd, infd;
    int wstatus;
    pid_t pid;

    if (argc != 4)
    {
        exit(EXIT_FAILURE);
    }

    cmd = argv[1];

    infd = open(argv[2], O_RDONLY);
    if (!infd)
    {
        perror("open infd");
        exit(EXIT_FAILURE);
    }

    outfd = open(argv[3], O_CREAT|O_WRONLY|O_TRUNC, 0666);
    if (!outfd)
    {
        perror("open outfd");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0)
    {
        close(infd);
        close(outfd);
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (!pid)
    {
        dup2(infd, 0);
        close(infd);

        dup2(outfd, 1);
        close(outfd);

        execlp(cmd, cmd, NULL);
        exit(EXIT_FAILURE);
    } else
    {
        close(infd);
        close(outfd);
        waitpid(pid, &wstatus, 0);
        if (WIFEXITED(wstatus)) exit(WEXITSTATUS(wstatus));
        else exit(EXIT_FAILURE);
    }

    return 0;
}
*/
