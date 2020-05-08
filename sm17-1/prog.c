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
    int status;
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
        exit(EXIT_SUCCESS);
    } else {
        close(infd);
        close(outfd);
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) exit(WEXITSTATUS(status));
        else exit(EXIT_FAILURE);
    }

    return 0;
}

// https://stackoverflow.com/questions/44221222/how-to-use-execlp-with-redirected-output
