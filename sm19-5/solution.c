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

#define NSTR 132
#define MYSIG (SIGUSR1)

int startPingPong(int* fd, int fdx, int n, int nn, const int *pn0) {
    pid_t pid, mypid, otherpid;
    int x;
    FILE *fin, *fout;
    char str[NSTR];

    int sign(int sfd) {
        siginfo_t siginfo;
        int res;
        res=read(sfd, &siginfo, sizeof(siginfo));
#if DEBUG
        printf(" %d", res);
        fflush(stdout);
        usleep(100000);
#endif
        return res==sizeof(siginfo)?1:0;
//(siginfo.si_pid == pid);
    }

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
            usleep(1000);
            fprintf(fout, "%d\n", mypid); fflush(fout);
            while(!sign(fdx)) ;
            fgets(str, NSTR-1, fin);
#if DEBUG
            printf("%d: str1=%s",n, str); fflush(stdout);
#endif
            sscanf(str, "%d", &otherpid);
            fprintf(fout, "%d\n", 1); fflush(fout);
            kill(otherpid, MYSIG);
        } else {
            fgets(str, NSTR-1, fin);
#if DEBUG
            printf("(%d): str1=%s",n,str); fflush(stdout);
#endif
            sscanf(str, "%d", &otherpid);
            fprintf(fout, "%d\n", mypid); fflush(fout);
            usleep(100);
            kill(otherpid, MYSIG);
        }
#if DEBUG
        printf("-- n=%d pid=%d otherpid=%d\n",n,getpid(),otherpid); fflush(stdout);
#endif
        while(!feof(fin)) {
#if DEBUG
            printf(","); fflush(stdout);
#endif
            while(!sign(fdx)) ;
            fgets(str, NSTR-1, fin);
            if(sscanf(str, "%d", &x)!=1) break;
#if DEBUG
            printf("%d: str2=%s",n,str); fflush(stdout);
#endif
            if(x>=nn) break;
            printf("%d send %d\n", n, x); fflush(stdout);
            fprintf(fout, "%d\n", x+1); fflush(fout);
            kill(otherpid, MYSIG);
        }
        fclose(fin);
        fclose(fout);
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

    usleep(1000);
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
    printf("nn=%d\n",nn);  fflush(stdout);
#endif

    sigemptyset(&mask);
    sigaddset(&mask, MYSIG); 
//    sigfillset(&mask); 
    fdx = signalfd(-1, &mask, 0);
//    fdx = signalfd(-1, &mask, SFD_NONBLOCK);
    rv=solution(nn, fdx);
    close(fdx);
    return rv;
}
