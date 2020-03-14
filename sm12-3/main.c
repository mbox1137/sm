#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>
#include "read_file.h"

const static int m=sizeof(struct FileContent);

int main(int argc, char **argv)
{
    int h,h2;
    int k, fsize;
    char fn[80]="main.tst";
    char fn2[80];
    struct FileContent fc={0, NULL};
    if(argc==3) {
        sscanf(argv[1],"%s",fn);
        sscanf(argv[1],"%s",fn2);
    }
    h=open(fn, O_RDONLY);
    h2=creat(fn2, 0644);
    if(h!=0 && h2!=0) {
        fc=read_file(h);
        write(h2, fc.data, fc.size);
    }
    free(fc.data);
    close(h);
    close(h2);
    return(0);
}
