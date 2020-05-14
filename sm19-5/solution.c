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

int startPingPong(int* fd, int n, int nn, const int *pn0) {
    pid_t pid, otherpid;
    int x;
    FILE *fin, *fout;
    char str[NSTR];
    int fdx;
    sigset_t mask;

    int sign(pid_t pid, int sfd) {
        siginfo_t siginfo;
        if(read(sfd, &siginfo, sizeof(siginfo))==sizeof(siginfo))
            return siginfo.si_pid == pid;
        return 0;
    }

    sigemptyset(&mask);
    sigaddset(&mask, MYSIG); 
    fdx=signalfd(-1, &mask, 0);

    pid=fork();
    if(pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        fin = fdopen(fd[0], "r");
        fout = fdopen(fd[1], "w");
        if(pn0) {
            fprintf(fout, "%d\n", getpid()); fflush(fout);
            fscanf(fin, "%d", &otherpid); fgets(str, NSTR-1, fin);
            fprintf(fout, "%d\n", 1); fflush(fout);
        } else {
            fscanf(fin, "%d", &otherpid); fgets(str, NSTR-1, fin);
            fprintf(fout, "%d\n", getpid()); fflush(fout);
        }
        while(	sign(otherpid, fdx) &&
                !feof(fin) && 
                fscanf(fin, "%d", &x)==1 && 
                x<nn) {
            printf("%d %d\n", n, x);
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

int main(int argc, char** argv) {
    int fd[2];
    int cpids[2];
    const int dummy=1;
    int k;
    int status;
    int nn;
    
    if(argc!=2 || sscanf(argv[1],"%d",&nn)!=1) return(0);
    if(nn<0) return 0;
    else if(nn==0) return 0;
    else if(nn==1) return 0;
#if DEBUG
    printf("nn=%d\n",nn);
#endif

    pipe(fd);

    cpids[0]=startPingPong(fd, 1, nn, NULL);
    cpids[1]=startPingPong(fd, 2, nn, &dummy);

    close(fd[0]);
    close(fd[1]);
#if DEBUG
    printf("cpid[0]=%d cpid[1]=%d\n",cpids[0], cpids[1]);
#endif

    for(k=0; k<2; k++) {
        waitpid(cpids[k], &status, 0);
        if (WIFEXITED(status)) continue;	//return WEXITSTATUS(status);
        else return EXIT_FAILURE;
    }
//    printf("Done\n");
}
