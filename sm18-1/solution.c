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
    if (argc != 3)
        exit(EXIT_FAILURE);

    int pipefd[2];
    pid_t cpid;
    int fdin, fdout;
    char *cmd = argv[1];

    if (pipe(pipefd) == -1)
        exit(EXIT_FAILURE);

    fdin = fork();

    if (fdin == -1)
        exit(EXIT_FAILURE);

    if (!fdin)
    {
        dup2(pepifd[1], 1);

        close(pipefd[0]);
        close(pipefd[1]);

        execlp(cmd, cmd, (char *) NULL);

        _exit(1);
    }

    cmd = argv[2];
    fdout = fork();

    if (fdout == -1)
        exit(EXIT_FAILURE);

    if (!fdout)
    {
        dup2(pipefd[0], 0);

        close(fd[0]);
        close(fd[1]);

        execlp(cmd, cmd, (char *) NULL);

        _exit(1);
    }

    close(fd[0]);
    close(fd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}

// man pipe
