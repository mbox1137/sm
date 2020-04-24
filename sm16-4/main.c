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
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <malloc.h>

    int
    main(int argc, char *argv[])
    {
        pid_t cpid, mypid;
        int n;
        int exitstatus;

        if (argc != 1) {
            fprintf(stderr, "Usage: %s <main.tst\n", argv[0]);
            exitstatus=EXIT_FAILURE;
            exit(exitstatus);
        }

        mypid=getpid();
        for(;;) {
            if(scanf("%d",&n)!=1)
                exit(EXIT_SUCCESS);
            cpid = fork();
            if (cpid == -1) {
                perror("fork");
                printf("-1\n");
                exitstatus=EXIT_FAILURE;
                exit(exitstatus);
            }
            if (cpid == 0) {      /* Child */
                continue;
            } else {          /* Parent */
                wait(NULL);             /* Wait for child */
                printf("%d\n",n);
//                fflush(NULL);
                break;
            }
        }
        if(mypid==getpid())
            exit(EXIT_SUCCESS);
    }
