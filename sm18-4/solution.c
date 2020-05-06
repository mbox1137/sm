#define DEBUG 1
//https://stackoverflow.com/questions/43349397/why-fprintf-and-fscanf-does-not-work-with-pipe
#define _POSIX_C_SOURCE 200101L
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int startPingPong(FILE* newstdin, FILE* newstdout, int n, const int *n0) {	//pid
    pid_t pid;
    pid=fork();
    if(pid == -1) {
        perror("fork");
        fclose(newstdin);
        fclose(newstdout);
        exit(EXIT_FAILURE);
    }
    if(pid==0) {	//child
        exit(EXIT_SUCCESS);
    } else {		//parent
        return(pid);
    }
}

int main() {
    int fd12[2], fd21[2];
    int cpids[2];
    const int dummy=1;

    pipe(fd12);
    pipe(fd21);

    FILE* wf12 = fdopen(fd12[1], "w");
    FILE* rf12 = fdopen(fd12[0], "r");
    FILE* wf21 = fdopen(fd21[1], "w");
    FILE* rf21 = fdopen(fd21[0], "r");

    cpids[0]=startPingPong(rf21, wf12, 1, &dummy);
    cpids[1]=startPingPong(rf12, wf21, 2, NULL);

    int x = 0;
    fprintf(wf12, "%d\n", 100);
    fflush(wf12);
    fscanf(rf12, "%d", &x);

    printf("%d\n", x);
}

/*
PIPE(2)                    Linux Programmer's Manual                   PIPE(2)

NAME
       pipe, pipe2 - create pipe

SYNOPSIS
       #include <unistd.h>

       struct fd_pair {
           long fd[2];
       };
       struct fd_pair pipe();

       int pipe(int pipefd[2]);

       #define _GNU_SOURCE
       #include <fcntl.h>
       #include <unistd.h>

       int pipe2(int pipefd[2], int flags);

EXAMPLE
       The  following  program  creates  a pipe, and then fork(2)s to create a
       child process; the child inherits a duplicate set of  file  descriptors
       that  refer  to  the same pipe.  After the fork(2), each process closes
       the file descriptors that it doesn't need for the pipe  (see  pipe(7)).
       The  parent  then writes the string contained in the program's command-
       line argument to the pipe, and the child reads this string a byte at  a
       time from the pipe and echoes it on standard output.

   Program source
       #include <sys/types.h>
       #include <sys/wait.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <string.h>

       int
       main(int argc, char *argv[])
       {
           int pipefd[2];
           pid_t cpid;
           char buf;

           if (argc != 2) {
               fprintf(stderr, "Usage: %s <string>\n", argv[0]);
               exit(EXIT_FAILURE);
           }

           if (pipe(pipefd) == -1) {
               perror("pipe");
               exit(EXIT_FAILURE);
           }

           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {
               close(pipefd[1]);

               while (read(pipefd[0], &buf, 1) > 0)
                   write(STDOUT_FILENO, &buf, 1);

               write(STDOUT_FILENO, "\n", 1);
               close(pipefd[0]);
               _exit(EXIT_SUCCESS);

           } else {
               close(pipefd[0]);
               write(pipefd[1], argv[1], strlen(argv[1]));
               close(pipefd[1]);
               wait(NULL);
               exit(EXIT_SUCCESS);
           }
       }
*/
