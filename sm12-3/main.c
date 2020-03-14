#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
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
        sscanf(argv[2],"%s",fn2);
    }
    h=open(fn, O_RDONLY);
    h2=creat(fn2, 0644);
    if(h!=0 && h2!=0) {
        fc=read_file(h);
        if(fc.data!=NULL && fc.size>=0 && fc.data[fc.size]==0)
            write(h2, fc.data, fc.size);
    }
    free(fc.data);
    close(h);
    close(h2);
    return(0);
}
