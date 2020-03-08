#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "binrev.h"

static struct Data ledata;

int main(int argc, char **argv)
{
    char fn[80];
    int k, n, m;
    int h;  
    m=sizeof(struct Data);
/*
    printf("sizeof(int16_t)=%d\n",sizeof(int16_t));
    printf("sizeof(struct Data)=%d\n",sizeof(struct Data));
*/
    fn[0]=0;
    if(argc==3) {
        sscanf(argv[1],"%s",fn);
        sscanf(argv[2],"%d",&n);
    }
    printf("%s %d\n",fn,n);
//    h=open(fn, O_WRONLY|O_CREAT , 0644);
    h=creat(fn, 0644);
    for(k=0; k<n; k++) {
        ledata.x=k;
        ledata.y=k*1000+k;
        write(h, &ledata, m);
    }
    close(h);
    return(0);
}
