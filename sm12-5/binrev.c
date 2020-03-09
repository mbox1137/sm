#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include "binrev.h"

int main(int argc, char **argv)
{
    char fn[80];
    int k, a, m, n, fsize;
    int h, htmp;
    struct stat st;
    struct Data d1, d2;
    m=sizeof(struct Data);
    unsigned char dc1[m], dc2[m];
    long tmp;
    fn[0]=0;
    a=-1;
    if(argc==3) {
        sscanf(argv[1],"%s",fn);
        sscanf(argv[2],"%d",&a);
    }
//    printf("%s %d\n",fn,a);
    if(stat(fn, &st)!=0) goto err2;
    fsize = st.st_size;
    n=fsize/m;
    if((h=open(fn, O_RDWR))==0) goto err2;
    for(k=0; k<n/2; k++) {
        if(lseek(h, k*m, SEEK_SET)==-1) goto err2;
        if(read(h, dc1, m)!=m) goto err2;
        unmarshall(&d1, dc1);
//        d1.y+=d1.x*a;	//ovf?
        if(__builtin_mul_overflow(d1.x, a, &tmp)) goto err3;
        if(__builtin_add_overflow(d1.y, tmp, &d1.y)) goto err3;

        if(lseek(h, (n-k-1)*m, SEEK_SET)==-1) goto err2;
        if(read(h, dc2, m)!=m) goto err2;
        unmarshall(&d2, dc2);
//        d2.y+=d2.x*a;	//ovf?
        if(__builtin_mul_overflow(d2.x, a, &tmp)) goto err3;
        if(__builtin_add_overflow(d2.y, tmp, &d2.y)) goto err3;

        marshall(dc2, &d2);
        if(lseek(h, k*m, SEEK_SET)==-1) goto err2;
        if(write(h, dc2, m)!=m) goto err2;
        marshall(dc1, &d1);
        if(lseek(h, (n-k-1)*m, SEEK_SET)==-1) goto err2;
        if(write(h, dc1, m)!=m) goto err2;
    }
//        printf("%d %lld\n", ledata.x, ledata.y);
    if(close(h)!=0) goto err2;
    return(0);
err3:
    fprintf(stderr,"OVF Err\n");
    return(3);
err2:
    fprintf(stderr,"I/O Err\n");
    return(2);
}
