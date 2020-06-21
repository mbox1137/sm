#define STDERR 0
#define NN 132

#include <unistd.h>
#include <stdio.h>

void main() {
    int x;
    int nc;
#if STDERR
    char lin[NN];
#endif
    while(!feof(stdin)) {
        if(scanf("%d",&x)==1) {
            nc=printf("%d\n", x+1);
            fflush(stdout);
#if STDERR
            if(nc<0) {
                sprintf(lin, "%d: printf(%d)", getpid(),x-1);
                perror(lin);
            }
            sprintf(lin, "%d: x=%d", getpid(), x);
            fprintf(stderr,"%s\n",lin);
#endif
        } else {
            fgetc(stdin);
        }
    }
    nc=nc;
}
