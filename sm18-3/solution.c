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
    if (argc != 5)
        exit(EXIT_FAILURE);

    pid_t pid1, pid2, pid3;
    int pipefd[2];
    char *cmd1 = argv[1], *cmd2 = argv[2], *cmd3 = argv[3], *filename = argv[4];
    int fd;

#if DEBUG
    printf("%s %s %s %s\n", cmd1, cmd2, cmd3, filename);
#endif

    if (pipe(pipefd) == -1)
        exit(EXIT_FAILURE);

    pid1 = fork();

    if (pid1 == -1)
        exit(EXIT_FAILURE);

    if (!pid1)
    {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        close(pipefd[1]);
        execlp("/bin/sh", "sh", "-c", cmd1, NULL);
        exit(1);
    }

    waitpid(pid1, 0, 0);

    pid2 = fork();

    if (pid2 == -1)
        exit(EXIT_FAILURE);

    if (!pid2)
    {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        close(pipefd[1]);
        execlp("/bin/sh", "sh", "-c", cmd2, NULL);
        exit(1);
    }

    waitpid(pid2, 0, 0);

    pid3 = fork();

    if (pid3 == -1)
        exit(EXIT_FAILURE);

    if (!pid3)
    {
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);

        if (fd < 0)
            exit(EXIT_FAILURE);

        dup2(pipefd[0], 0);
        dup2(fd, 1);
        close(pipefd[0]);
        close(pipefd[1]);
        execlp("/bin/sh", "sh", "-c", cmd3, NULL);
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid2, 0, 0);
    waitpid(pid3, 0, 0);

    exit(EXIT_SUCCESS);
}

