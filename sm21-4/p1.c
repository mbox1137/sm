#define STDERR 1
#define NN 132

#include <unistd.h>
#include <stdio.h>

void main() {
    int x, nc;
    char lin[NN];
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
            fprintf(stderr,"%s",lin);
#endif
        } else {
            fgetc(stdin);
        }
    }
}
