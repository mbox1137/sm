#define DEBUG 1
#define WRITE 1

//http://www.opennet.ru/base/dev/unix_signals.txt.html

    #include <signal.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <malloc.h>
    #include <fcntl.h>

    int startArithmeticProgression(int h, int a0, int d, int k) {	//pid
        pid_t cpid, mypid;
        int a;
        cpid=fork();
        if(cpid==0) {	//child
            a=a0;
            mypid=getpid();
            for(;;) {
//                usleep(0.5E6);
                kill(mypid, SIGSTOP);
#if WRITE
//        lseek(h, n*k*sizeof(int), SEEK_SET);
                write(h, &a, sizeof(int));
#else
                printf("%d: a=%d\n", mypid, a);
#endif
                a+=d;
            }
        } else {	//parent
            return(cpid);
        }
    }

    int
    main(int argc, char *argv[])
    {
        int n, a0, d, k, i, j;
        int h;
        char f[132];
        pid_t *cpids;
        siginfo_t infop;

        n=3;
        strcpy(f,"out.bin");
        a0=4;
        d=2;
        k=4;

#if DEBUG
        printf("N=%d F=%s A0=%d D=%d K=%d\n",n,f,a0,d,k);
//        sleep(1);
#endif
//----------------------------------------------- без пайпов!!!
        h=creat(f,0664);
        cpids=malloc(n*sizeof(pid_t));
        if(cpids==NULL) {
            return(-1);
        }
        for(i=0; i<n; i++) {
            cpids[i]=startArithmeticProgression(h, a0+d*i, d*n, k);
        }
        for(j=0; j<k; j++) {
            for(i=0; i<n; i++) {
                for(;;) {
                    infop.si_code=0;
                    waitid(P_PID, cpids[i], &infop, WSTOPPED);
                    if(infop.si_code==CLD_STOPPED)
                        break;
                }
                kill(cpids[i], SIGCONT);
                for(;;) {
                    infop.si_code=0;
                    waitid(P_PID, cpids[i], &infop, WCONTINUED);
                    if(infop.si_code==CLD_CONTINUED)
                        break;
                }
                usleep(499);
            }
        }
        for(i=0; i<n; i++) {
            for(;;) {
                waitid(P_PID, cpids[i], &infop, WEXITED|WSTOPPED);
                if(infop.si_code==CLD_STOPPED || infop.si_code==CLD_EXITED)
                    break;
            }
        }
        for(i=0; i<n; i++) {
            kill(cpids[i], SIGTERM);
            kill(cpids[i], SIGCONT);
        }
        wait(NULL);
        free(cpids);
        close(h);
        return(0);
    }
