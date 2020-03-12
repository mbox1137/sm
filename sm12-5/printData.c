#define _GNU_SOURCE
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "binrev.h"

static struct Data data;

int main(int argc, char **argv)
{
    char fn[80];
    int k, m, nrb;
    int h;  
    m=sizeof(struct Data);
    if(argc==2) {
        sscanf(argv[1],"%s",fn);
    }
    h=open(fn, O_RDONLY);
    k=0;
    while(1) {
        nrb=read(h, &data, m);
        if(nrb!=m)
            break;
        printf("%hd %" PRId64 "\n", data.x, data.y);
        k++;
    }
    close(h);
    return(0);
}
