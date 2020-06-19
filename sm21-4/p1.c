#define STDERR 1
#define NN 132

#include <unistd.h>
#include <stdio.h>

void main() {
    int x, nx;
    int nc, s;
#if STDERR
    char lin[NN];
    fprintf(stderr, "%d\n", getpid());
#endif
    s=0;
    for(;;) {
        for(;;) {
            if(feof(stdin)) break;
            if((nx=scanf("%d",&x))==1) break;
        }
        if(feof(stdin)) break;
        if(nx!=1) break;
#if STDERR
        fprintf(stderr, "%d: %d\n", getpid(), x);
#endif
        s+=x;
    }
    nc=printf("%d\n", s);
    fflush(stdout);
#if STDERR
    if(nc<0) {
        sprintf(lin, "%d: printf(%d)", getpid(),x-1);
        perror(lin);
    }
    sprintf(lin, "%d: s=%d", getpid(), s);
    fprintf(stderr,"%s\n",lin);
#endif
    nc=nc;
}
