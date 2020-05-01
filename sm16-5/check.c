#define DEBUG 0
#define NN 10

#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int n, a, retval, a0, d, k, i;
    int h;
    char f[132];
    int nn;

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
    h = open(f, O_RDONLY);
    i=0;
    retval=0;
    for(;;) {
        for(nn=0; nn<NN; nn++) {
            lseek(h, i*sizeof(int), SEEK_SET);
            if(read(h,&a,sizeof(int))==sizeof(int))
                break;
        }
        if(nn==NN)
            break;
        if(a!=a0+i*d) {
            retval=1;
            break;
        }
//        printf("i=%d\n",i);
        i++;
    }
    close(h);
    if(i!=n*k)
        retval=2;
    return(retval);
}

// http://www.opennet.ru/base/dev/unix_signals.txt.html

