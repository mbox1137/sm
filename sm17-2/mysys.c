#define DEBUG 1

#include "mysys.h"

int mysys(const char *str) {
    return(0);
}

/*
#define _POSIX_C_SOURCE 200101L
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
    int k;
    int status;
    pid_t pid;

    if(argc != 4) {
        for(k=1;k<argc;k++)
            fprintf(stderr,"%d %s\n", k, argv[k]);
        fprintf(stderr,"./prog wc in.txt out.txt\n");
        return(1);
    } else {
        cmd=argv[1];
        infd = open(argv[2], O_RDONLY);
        outfd = open(argv[3], O_CREAT|O_WRONLY|O_TRUNC, 0644);
    }

    if (!infd)
    {
        perror("open infd");
        return EXIT_FAILURE;
    }
    if (!outfd)
    {
        perror("open outfd");
        return EXIT_FAILURE;
    }
    pid = fork();
    if (pid < 0)
    {
        close(infd);
        close(outfd);
        perror("fork");
        return EXIT_FAILURE;
    }

    if(!pid)
    {
        // child code
        dup2(infd, 0); // replace stdin
        close(infd);
        dup2(outfd, 1); // replace stdout
        close(outfd);
        execlp(cmd, "-", NULL);
    }
    else
    {
        // parent code
        close(infd);
        close(outfd);
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) return WEXITSTATUS(status);
        else return EXIT_FAILURE;
    }
}
*/
