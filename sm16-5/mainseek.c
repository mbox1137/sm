#define DEBUG 0
#define NN 10
#define _GNU_SOURCE 1

#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <fcntl.h>
#include <sys/file.h>

int startArithmeticProgression(int h, int i, int n, int a0, int d, int k) { //pid
    pid_t cpid;
    int a, j;
    off_t off;
    size_t siz;
    int nn, nnn;

    cpid = fork();
    if (cpid == 0)
    {
        for(j = 0; j < k; j++)
        {
            for(nn=0;nn<NN;nn++) {
                printf(" j%d",j);
                if(flock(h, LOCK_EX))
                    usleep(10);
                else
                    break;
            }
            if(nn==NN){
            }
            for(nnn=0;nnn<NN;nnn++) {
                off=(i + j * n) * sizeof(int);
                for(nn=0;nn<NN;nn++)
                    if(lseek(h, off, SEEK_SET)==off)
                        break;
                if(nn==NN){
                }
                a = a0+j*d;
                siz=sizeof(int);
                for(nn=0;nn<NN;nn++) {
                    printf(" w%d",j);
                    if(write(h, &a, siz)==siz)
                        break;
                }
                if(nn==NN){
                }
            }
            sync();
//            syncfs(h);
            for(nn=0;nn<NN;nn++) {
                printf(" J%d",j);
                if(flock(h, LOCK_UN))
                    usleep(10);
                else
                    break;
            }
            if(nn==NN){
            }
            a += d;
        }
        _exit(EXIT_SUCCESS);	//Do nothing else
    } else
        return(cpid);
}

int main(int argc, char *argv[])
{
    int n, a0, d, k, i;
    int h;
    char f[132];
    pid_t *cpids;

    if (argc == 1)
    {
        n = 3;
        strcpy(f, "out.bin");
        a0 = 4;
        d = 2;
        k = 4;
    } else if (argc == 6) {
        if(sscanf(argv[1], "%d", &n) != 1)
            exit(1);
        if(sscanf(argv[2], "%s", f) != 1)
            exit(1);
        if(sscanf(argv[3], "%d", &a0) != 1)
            exit(1);
        if(sscanf(argv[4], "%d", &d) != 1)
            exit(1);
        if(sscanf(argv[5], "%d", &k) != 1)
            exit(1);
    } else {
        fprintf(stderr, "%s: 3 out.bin 4 2 4", argv[0]);
        exit(1);
    }
#if DEBUG
    printf("N=%d F=%s A0=%d D=%d K=%d\n", n, f, a0, d, k);
#endif
    h = creat(f, S_IRUSR|S_IWUSR| S_IRGRP| S_IROTH);

    cpids = malloc(n * sizeof(pid_t));
    if(cpids == NULL)
        return -1;

    for(i = 0; i < n; i++)
        cpids[i] = startArithmeticProgression(h, i, n, a0 + d * i, d * n, k);

    wait(NULL);

    free(cpids);

    close(h);

    return 0;
}

// http://www.opennet.ru/base/dev/unix_signals.txt.html

