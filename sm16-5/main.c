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

    int startArithmeticProgression(int a0, int d, int k) {	//pid
        pid_t cpid;
        cpid=fork();
        if(cpid==0) {	//child
            kill(getpid(), SIGSTOP);
            sleep(10);
        } else {	//parent
            return(cpid);
        }
    }

/*
3 out.bin 4   2  4
N,   F,   A0, D, K
*/
    int
    main(int argc, char *argv[])
    {
        int exitstatus;
        int n, a0, d, k, i;
        char f[132];
        pid_t *cpids;

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
        cpids=malloc(n*sizeof(pid_t));
        if(cpids==NULL) {
        }
        for(i=0; i<n; i++) {
            cpids[i]=startArithmeticProgression(a0, d, k);
        }
        for(i=0; i<n; i++) {
            kill(cpids[i], SIGCONT);
        }
        wait(NULL);
        free(cpids);
        return(0);
exit:
        exit(exitstatus);
    }
