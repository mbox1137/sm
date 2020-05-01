#define DEBUG 1
//https://stackoverflow.com/questions/44221222/how-to-use-execlp-with-redirected-output
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

        if(argc != 4) {
            for(k=1;k<argc;k++)
                fprintf(stderr,"%d %s\n", k, argv[k]);
            fprintf(stderr,"./prog wc in.txt out.txt\n");
            return(1);
        } else {
            file=argv[1];
            arg2=argv[2];
            arg4=argv[3];
            sprintf(fn1,"<%s",argv[2]);
            sprintf(fn2,">%s",argv[3]);
        }
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

/*
'>' is not a parameter, it is normally interpreted by a shell. If you want to achieve the same effect in C code, you have to do the same thing the shell normally does:

    open a file (1.txt) for writing
    fork() a new process
    [in child] replace the stdout of the new process with the file's descriptor using dup2()
    [in child] exec the command

Simplified example code for POSIX:

#define _POSIX_C_SOURCE 200101L
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int outfd = open("1.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    if (!outfd)
    {
        perror("open");
        return EXIT_FAILURE;
    }
    pid_t pid = fork();
    if (pid < 0)
    {
        close(outfd);
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid)
    {
        // child code
        dup2(outfd, 1); // replace stdout
        close(outfd);

        // just a "useless cat" for simplicity:
        execlp("cat", "cat", "redir.c", 0);
    }
    else
    {
        // parent code
        close(outfd);
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) return WEXITSTATUS(status);
        else return EXIT_FAILURE;
    }
}
*/
