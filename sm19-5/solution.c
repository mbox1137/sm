#define DEBUG 1

//https://stackoverflow.com/questions/43349397/why-fprintf-and-fscanf-does-not-work-with-pipe
//#define _POSIX_C_SOURCE 200101L
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <string.h> 

#define NSTR 132
#define MYSIG (SIGUSR1)

//https://www.linuxprogrammingblog.com/code-examples/signalfd

int waitSIG (int sfd, int sig){
	sigset_t mask; 	/* We will handle SIGTERM and SIGINT. */
	struct signalfd_siginfo si;
	ssize_t res;

	sigemptyset (&mask);
	sigaddset (&mask, sig);

/* Block the signals thet we handle using signalfd(), so they don't
 * cause signal handlers or default signal actions to execute. */
	if (sigprocmask(SIG_BLOCK, &mask, NULL) < 0) {
		return 0;
	}

	res = read (sfd, &si, sizeof(si));
	if (res < 0) {
		return 0;
	}
	if (res != sizeof(si)) {
		return 0;
	}
	return(si.ssi_signo == sig?1:0);
}

int startPingPong(int* fd, int fdx, int n, int nn, const int *pn0) {
    pid_t pid, mypid, otherpid;
    int x;
    FILE *fin, *fout;
    char str[NSTR];
    int  eof, wsig, gs, scan;
#if DEBUG
    char *tabs[] = { "", "\t", "\t\t\t" };
#endif

    pid=fork();
    if(pid == -1) {
        perror("fork");
        return(-1);
    }
    if (pid == 0) {
        mypid=getpid();
        fin = fdopen(fd[0], "r");
        fout = fdopen(fd[1], "w");
        if(pn0) {
            fprintf(fout, "%d\n", mypid); fflush(fout);
            while(!waitSIG(fdx, MYSIG)) ;
            fgets(str, NSTR-1, fin);
#if DEBUG
            printf("%d:%s str1=%s", n, tabs[n], str); fflush(stdout);
#endif
            sscanf(str, "%d", &otherpid);
            fprintf(fout, "%d\n", 1); fflush(fout);
            kill(otherpid, MYSIG);
        } else {
            fgets(str, NSTR-1, fin);
#if DEBUG
            printf("%d:%s str1=%s",n,tabs[n],str); fflush(stdout);
#endif
            sscanf(str, "%d", &otherpid);
            fprintf(fout, "%d\n", mypid); fflush(fout);
//            usleep(100);
            kill(otherpid, MYSIG);
        }
#if DEBUG
        printf("%d:%s pid=%d otherpid=%d\n",n,tabs[n],getpid(),otherpid); fflush(stdout);
#endif
        while(1) {
#if DEBUG
            printf("%d:%s \n",n,tabs[n]); fflush(stdout);
#endif
            eof=feof(fin);
#if DEBUG
            printf("%d:%s eof=%d\n",n,tabs[n],eof); fflush(stdout);
#endif
            if(eof) break;
//----------
            wsig=waitSIG(fdx, MYSIG);
#if DEBUG
            printf("%d:%s wsig=%d\n",n,tabs[n],wsig); fflush(stdout);
#endif
            if(!wsig) break;
//----------
#if DEBUG
            printf("%d:%s gets=...\n",n,tabs[n]); fflush(stdout);
#endif
            gs = (fgets(str, NSTR-1, fin) != NULL);
#if DEBUG
            printf("%d:%s str=%s",n,tabs[n],str); fflush(stdout);
#endif
#if DEBUG
            printf("%d:%s gs=%d\n",n,tabs[n],gs); fflush(stdout);
#endif
            if(!gs) break;
//----------
            scan =  sscanf(str, "%d", &x);
#if DEBUG
            printf("%d:%s scan=%d x=%d\n",n,tabs[n],scan, x); fflush(stdout);
#endif
            if(! ((scan==1)&&(x<nn)) ) break;
#if DEBUG
            printf("%d:%s -> (%d)\n", n,tabs[n], x+1); fflush(stdout);
#else
            printf("%d %d\n", n, x); fflush(stdout);
#endif
            fprintf(fout, "%d\n", x+1); fflush(fout);
            kill(otherpid, MYSIG);
        }
        fprintf(fout, "\n"); fflush(fout);
        kill(otherpid, MYSIG);
        fclose(fin);
        fclose(fout);
        close(fd[0]);
        close(fd[1]);
        exit(EXIT_SUCCESS);
    } else {
        return(pid);
    }
}

int solution(int nn, int fdx) {
    int fd[2];
    int cpids[2];
    const int dummy=1;
    int k;
    int status;
    int rv;

//    usleep(1000);
    pipe(fd);
    cpids[0]=startPingPong(fd, fdx, 1, nn, NULL);
    cpids[1]=startPingPong(fd, fdx, 2, nn, &dummy);
    close(fd[0]);
    close(fd[1]);
#if DEBUG
    printf("cpid[0]=%d cpid[1]=%d\n",cpids[0], cpids[1]); fflush(stdout);
#endif
    rv=0;
    for(k=0; k<2; k++) {
        waitpid(cpids[k], &status, 0);
        if (WIFEXITED(status)) rv |= WEXITSTATUS(status);
        else if (WIFSIGNALED(status)) rv |= 1024+WTERMSIG(status);
/*
        if (WIFEXITED(status)) return(WEXITSTATUS(status));
        else if (WIFSIGNALED(status)) return(1024+WTERMSIG(status));
        else if (WIFSTOPPED(status)) return(1024+WSTOPSIG(status));
        else if (WIFCONTINUED(status)) return(1024+SIGCONT);
*/
    }
//    printf("Done\n");
    return rv;
}

int main(int argc, char** argv) {
    int nn;
    int fdx;
    int rv;
    sigset_t mask;

    if(argc!=2 || sscanf(argv[1],"%d",&nn)!=1) return(0);
    if(nn<0) return 0;
    else if(nn==0) return 0;
    else if(nn==1) return 0;
#if DEBUG
    printf("nn=%d pid=%d\n",nn, getpid());  fflush(stdout);
#endif
    sigemptyset(&mask);
    sigaddset(&mask, MYSIG); 
//    sigfillset(&mask); 
    if (sigprocmask(SIG_BLOCK, &mask, NULL) < 0) {
#if DEBUG
        perror ("sigprocmask");
#endif
        return 1;
    }
    fdx = signalfd(-1, &mask, 0);
//    fdx = signalfd(-1, &mask, SFD_NONBLOCK);
#if DEBUG
    printf("fdx=%d\n", fdx);
#endif
    rv=solution(nn+1, fdx);
    close(fdx);
    return rv;
}
