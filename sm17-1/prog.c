#define DEBUG 1
/*
https://stackoverflow.com/questions/44221222/how-to-use-execlp-with-redirected-output
'>' is not a parameter, it is normally interpreted by a shell. If you want to achieve the same effect in C code, you have to do the same thing the shell normally does:

    open a file (1.txt) for writing
    fork() a new process
    [in child] replace the stdout of the new process with the file's descriptor using dup2()
    [in child] exec the command
*/

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

/*
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <linux/limits.h>

    int
    main(int argc, char *argv[])
    {
        pid_t pid;
        char *file, *arg2, *arg4;
        char arg1[]="<", arg3[]=">";
        char fn1[PATH_MAX];
        char fn2[PATH_MAX];
        int k;

        pid=fork();
        if(pid==0) {
//            execlp(file, arg1, arg2, arg3, arg4, NULL);
            execlp(file, fn1, fn2, NULL);
            exit(0);
        } else {
            wait(NULL);
        }
        return(0);
    }
*/
