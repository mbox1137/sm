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
        pid_t cpid, mypid;
        cpid=fork();
        if(cpid==0) {	//child
            mypid=getpid();
            for(;;) {
                usleep(0.5*1E6);
                kill(mypid, SIGSTOP);
                printf("%d:\n", mypid);
            }
        } else {	//parent
            return(cpid);
        }
    }

    int
    main(int argc, char *argv[])
    {
        int exitstatus;
        int n, a0, d, k, i, j;
        char f[132];
        pid_t *cpids, pid;
        int wstatus;

        n=3;
        strcpy(f,"out.bin");
        a0=4;
        d=2;
        k=4;

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
        for(j=0; j<k; j++) {
//            sleep(1);
            for(i=0; i<n; i++) {
                for(;;) {
                    pid=waitpid(cpids[i], &wstatus, WUNTRACED);
                    if(WIFSTOPPED(wstatus))
                        break;
                }
                kill(pid, SIGCONT);
//            printf("\n");
            }
        }
        sleep(1);
        for(i=0; i<n; i++) {
            kill(cpids[i], SIGTERM);
            kill(cpids[i], SIGCONT);
        }
        wait(NULL);
        free(cpids);
        return(0);
exit:
        exit(exitstatus);
    }
