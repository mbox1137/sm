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
        int k, n;
        int exitstatus;

        if (argc != 2) {
            fprintf(stderr, "Usage: %s 3\n", argv[0]);
            exitstatus=EXIT_FAILURE;
            exit(exitstatus);
        }

        if(sscanf(argv[1],"%d",&n)!=1) {
            perror("sscanf");
            exitstatus=EXIT_FAILURE;
            exit(exitstatus);
        }

        mypid=getpid();
        if(n>0) {
            printf("%d",1);
            fflush(NULL);
        }
        for(k=2;k<=n;k++) {
            cpid = fork();
            if (cpid == -1) {
                perror("fork");
                exitstatus=EXIT_FAILURE;
                exit(exitstatus);
            }
            if (cpid == 0) {      /* Child reads from pipe */
                printf(" %d",k);
                fflush(NULL);
                continue;
            } else {          /* Parent writes argv[1] to pipe */
                wait(NULL);             /* Wait for child */
                break;
            }
        }
        if(mypid==getpid() && n>0)
            printf("\n");
        exit(EXIT_SUCCESS);
    }
