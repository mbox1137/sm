#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "binrev.h"

static struct Data ledata;

int main(int argc, char **argv)
{
    char fn[80];
    int k, a, m, n, fsize;
    int h;  
    struct stat st;
    m=sizeof(struct Data);
    fn[0]=0;
    if(argc==3) {
        sscanf(argv[1],"%s",fn);
        sscanf(argv[2],"%d",&a);
    }
    printf("%s %d\n",fn,n);
    stat(fn, &st);
    fsize = st.st_size;
    n=fsize/m;
    h=open(fn, O_RDONLY);
    for(k=0; k<n; k++) {
        read(h, &ledata, m);
        printf("%d %lld\n", ledata.x, ledata.y);
    }
    close(h);
    return(0);
}
