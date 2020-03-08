#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "binrev.h"

int main(int argc, char **argv)
{
    char fn[80];
    int k, a, m, n, fsize;
    int h, htmp;
    struct stat st;
    struct Data d1, d2;
    m=sizeof(struct Data);
    fn[0]=0;
    if(argc==3) {
        sscanf(argv[1],"%s",fn);
        sscanf(argv[2],"%d",&a);
    }
    printf("%s %d\n",fn,a);
    stat(fn, &st);
    fsize = st.st_size;
    n=fsize/m;
    h=open(fn, O_RDWR);
    for(k=0; k<n/2; k++) {
        lseek(h, k*m, SEEK_SET);
        read(h, &d1, m);
        d1.y+=d1.x*a;	//ovf?

        lseek(h, (n-k-1)*m, SEEK_SET);
        read(h, &d2, m);
        d2.y+=d2.x*a;	//ovf?

        lseek(h, k*m, SEEK_SET);
        write(h, &d2, m);
        lseek(h, (n-k-1)*m, SEEK_SET);
        write(h, &d1, m);
    }
//        printf("%d %lld\n", ledata.x, ledata.y);
    close(h);
    return(0);
}
