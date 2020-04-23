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
        int *pipefd;
        pid_t cpid;
        char buf;
        int exitstatus;
        int n;

        if (argc != 2) {
            fprintf(stderr, "Usage: %s 3\n", argv[0]);
            exitstatus=EXIT_FAILURE;
            goto exit;
        }

        if(sscanf(argv[1],"%d",&n)!=1) {
            perror("sscanf");
            exitstatus=EXIT_FAILURE;
            goto exit;
        }

        if(!(pipefd=malloc(n*2*sizeof(int)))) {
            perror("malloc");
            exitstatus=EXIT_FAILURE;
            goto exit;
        }

        if (pipe(pipefd) == -1) {
            perror("pipe");
            exitstatus=EXIT_FAILURE;
            goto exit;
        }

        cpid = fork();
        if (cpid == -1) {
            perror("fork");
            exitstatus=EXIT_FAILURE;
            goto exit;
        }

        if (cpid == 0) {      /* Child reads from pipe */
            close(pipefd[1]);           /* Close unused write end */
            while (read(pipefd[0], &buf, 1) > 0)
                write(STDOUT_FILENO, &buf, 1);
            write(STDOUT_FILENO, "\n", 1);
            close(pipefd[0]);
            exitstatus=EXIT_SUCCESS;
            exit(exitstatus);
        } else {          /* Parent writes argv[1] to pipe */
            close(pipefd[0]);           /* Close unused read end */
            write(pipefd[1], argv[1], strlen(argv[1]));
            close(pipefd[1]);           /* Reader will see EOF */
            wait(NULL);             /* Wait for child */
            exitstatus=EXIT_SUCCESS;
            goto exit;
        }
exit:
        free(pipefd);
        exit(exitstatus);
    }
