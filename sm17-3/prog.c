#define DEBUG 0

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int process(char *cmd)
{
    pid_t proc;
    int wstatus;

#if DEBUG
    printf("cmd = %s\n", cmd);
#endif

    proc = fork();

    if (!proc)
    {
        execlp("/bin/sh", "sh", "-c", cmd, NULL);
        return 0;
    }

    waitpid(proc, &wstatus, 0);

    if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 0)
        return 1;
    else
        return 0;
}

int main(int argc, char *argv[])
{
#if DEBUG
    printf("%d\n", argc);
#endif

    if (argc != 4)
        exit(EXIT_FAILURE);

    if (process(argv[1]))
    {
        if (process(argv[3]))
            return 0;
        else
            return 1;
    }

    else if (process(argv[2]))
    {
        if (process(argv[3]))
            return 0;
        else
            return 1;
    }

    return 1;
}
