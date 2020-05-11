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
    pid_t pid1, pid2;
    char *cmd1 = argv[1], *cmd2 = argv[2];

    if (argc != 3)
        exit(EXIT_FAILURE);

    if (pipe(pipefd) == -1)
        exit(EXIT_FAILURE);

    pid1 = fork();
    if (pid1 == -1)
        exit(EXIT_FAILURE);
    if (!pid1)
    {
        dup2(pipefd[0], 0);
        close(pipefd[0]);
        close(pipefd[1]);
        execlp("/bin/sh", "sh", "-c", cmd2, NULL);
        exit(1);
    }

    close(pipefd[0]);
    
    pid2 = fork();
    if (pid2 == -1)
        exit(EXIT_FAILURE);
    if (!pid2)
    {
        dup2(pipefd[1], 1);
//        close(pipefd[0]);
        close(pipefd[1]);
        execlp("/bin/sh", "sh", "-c", cmd1, NULL);
        exit(1);
    }

    close(pipefd[1]);

    waitpid(pid1, 0, 0);
    waitpid(pid2, 0, 0);

    return 0;
}

// man pipe
