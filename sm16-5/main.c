#define DEBUG 1
//http://www.opennet.ru/base/dev/unix_signals.txt.html
/*
man 2 pipe

EXAMPLE
    The  following   program     creates     a pipe, and then fork(2)s to create a
    child process; the child inherits a duplicate set of    file    descriptors
    that    refer    to  the same pipe. After the fork(2), each process closes
    the file descriptors that it doesn't need for the pipe  (see    pipe(7)).
    The  parent  then writes the string contained in the program's command-
    line argument to the pipe, and the child reads this string a byte at    a
    time from the pipe and echoes it on standard output.
*/
    #include <signal.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <malloc.h>
/*
3 out.bin 4   2  4
N,   F,   A0, D, K
*/
    int
    main(int argc, char *argv[])
    {
        int *pipefd;
        pid_t cpid, mypid;
        char buf;
        int exitstatus;
        int n, a0, d, k;
        char f[132];

        if (argc != 6) {
            fprintf(stderr, "Usage: %s N FileName A0 D K\n", argv[0]);
            exitstatus=EXIT_FAILURE;
            goto exit;
        }

        if(sscanf(argv[1],"%d",&n)!=1) {
            perror("N?");
            exitstatus=EXIT_FAILURE;
            goto exit;
        }

        if(sscanf(argv[2],"%s",f)!=1) {
            perror("F?");
            exitstatus=EXIT_FAILURE;
            goto exit;
        }

        if(sscanf(argv[3],"%d",&a0)!=1) {
            perror("A0?");
            exitstatus=EXIT_FAILURE;
            goto exit;
        }

        if(sscanf(argv[4],"%d",&d)!=1) {
            perror("D?");
            exitstatus=EXIT_FAILURE;
            goto exit;
        }

        if(sscanf(argv[5],"%d",&k)!=1) {
            perror("K?");
            exitstatus=EXIT_FAILURE;
            goto exit;
        }
#if DEBUG
        printf("N=%d F=%s A0=%d D=%d K=%d\n",n,f,a0,d,k);
#endif
//----------------------------------------------- без пайпов!!!
        cpid=fork();
        if(cpid==0) {	//child
            kill(getpid(), SIGSTOP);
            sleep(1);
        } else {	//parent
            sleep(1);
            printf("...\n");
            sleep(1);
            kill(cpid, SIGCONT);
            wait(NULL);
        }
//        pause();
        return(0);
exit:
        exit(exitstatus);
    }
#if 0
       #include <sys/wait.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <stdio.h>

       int
       main(int argc, char *argv[])
       {
           pid_t cpid, w;
           int wstatus;

           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {            /* Code executed by child */
               printf("Child PID is %ld\n", (long) getpid());
               if (argc == 1)
                   pause();                    /* Wait for signals */
               _exit(atoi(argv[1]));

           } else {                    /* Code executed by parent */
               do {
                   w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
                   if (w == -1) {
                       perror("waitpid");
                       exit(EXIT_FAILURE);
                   }

                   if (WIFEXITED(wstatus)) {
                       printf("exited, status=%d\n", WEXITSTATUS(wstatus));
                   } else if (WIFSIGNALED(wstatus)) {
                       printf("killed by signal %d\n", WTERMSIG(wstatus));
                   } else if (WIFSTOPPED(wstatus)) {
                       printf("stopped by signal %d\n", WSTOPSIG(wstatus));
                   } else if (WIFCONTINUED(wstatus)) {
                       printf("continued\n");
                   }
               } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
               exit(EXIT_SUCCESS);
           }
       }
#endif
