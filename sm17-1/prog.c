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
    //int status;
    pid_t pid;

    if (argc != 4)
    {
        /*for(int k = 1; k < argc; k++)
            fprintf(stderr,"%d %s\n", k, argv[k]);
        fprintf(stderr,"./prog wc in.txt out.txt\n");*/
        exit(1);
    }

    cmd = argv[1];
    infd = open(argv[2], O_RDONLY);
    outfd = open(argv[3], O_CREAT|O_WRONLY|O_TRUNC, 0644);

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

    /*if (pid < 0)
    {
        close(infd);
        close(outfd);
        perror("fork");
        return EXIT_FAILURE;
    }*/

    if (!pid)
    {
        dup2(infd, 0);
        close(infd);

        dup2(outfd, 1);
        close(outfd);

        execlp(cmd, cmd, NULL);
        exit(1);
    }
    /*else {
        close(infd);
        close(outfd);
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) return WEXITSTATUS(status);
        else return EXIT_FAILURE;
    }*/

    wait(NULL);

    return 0;
}

// https://stackoverflow.com/questions/44221222/how-to-use-execlp-with-redirected-output
