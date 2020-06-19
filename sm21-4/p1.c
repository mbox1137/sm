#define STDERR 0
#define NN 132

#include <unistd.h>
#include <stdio.h>

void main() {
    int x;
    int nc, s;
#if STDERR
    char lin[NN];
#endif
    s=0;
    while(!feof(stdin)) {
        if(scanf("%d",&x)==1) {
            s+=x;
        } else {
            fgetc(stdin);
        }
    }
    nc=printf("%d\n", s);
    fflush(stdout);
#if STDERR
    if(nc<0) {
        sprintf(lin, "%d: printf(%d)", getpid(),x-1);
        perror(lin);
    }
    sprintf(lin, "%d: x=%d", getpid(), x);
    fprintf(stderr,"%s",lin);
#endif
    nc=nc;
}
