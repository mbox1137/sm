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
    int pipefd[2];
    int fdin, fdout;
    char *cmd1 = argv[1], *cmd2 = argv[2];

    if (argc != 3)
        exit(EXIT_FAILURE);

    if (pipe(pipefd) == -1)
        exit(EXIT_FAILURE);

    fdin = fork();

    if (fdin == -1)
        exit(EXIT_FAILURE);

    if (!fdin)
    {
        dup2(pipefd[1], 1);

        close(pipefd[0]);
        close(pipefd[1]);

        execlp(cmd1, cmd1, (char *) NULL);

        _exit(1);
    }

    fdout = fork();

    if (fdout == -1)
        exit(EXIT_FAILURE);

    if (!fdout)
    {
        dup2(pipefd[0], 0);

        close(pipefd[0]);
        close(pipefd[1]);

        execlp(cmd2, cmd2, (char *) NULL);

        _exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}

// man pipe
