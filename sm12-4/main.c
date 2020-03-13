#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>
#include "binary-tree.h"

const static int m=sizeof(struct Node);
static int nkeys;
static int *keys;
static int h;

int scan_tree(int nd);

int scan_tree(int nd) {
    int retcode;
    struct Node node;
    retcode=0;
    if(lseek(h,nd*m,SEEK_SET)!=nd*m || read(h, &node, m)!=m) {
        retcode=1;
    } else {
        if(node.left_idx !=0) retcode|=scan_tree(node.left_idx);
        if(node.right_idx!=0) retcode|=scan_tree(node.right_idx);
        keys[nkeys++]=node.key;
    }
    return(retcode);
}

static int cmpints(const void *p1, const void *p2) {
    return (*(int*)p2)-(*(int*)p1);
}

int main(int argc, char **argv)
{
    int k, fsize;
    struct stat st;
    char fn[80]="main.dat";
    if(argc==2) {
        sscanf(argv[1],"%s",fn);
    }
    nkeys=0;
    stat(fn, &st);
    fsize = st.st_size;
    nkeys=fsize/m;
    h=open(fn, O_RDONLY);
    keys=(int*) calloc(nkeys,sizeof(int));
    if(h!=0 && keys!=0) {
        nkeys=0;
        if(scan_tree(0)) {
            exit(-2);
        } else {
            qsort(keys, nkeys, sizeof(int), cmpints);
            for(k=0; k<nkeys; k++) printf("%d ",keys[k]); printf("\n");
        }
    } else {
        exit(-1);
    }
    free(keys);
    close(h);
    return(0);
}
