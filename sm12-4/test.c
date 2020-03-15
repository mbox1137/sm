#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>
#include "binary-tree.h"

static struct Node node;
const static int m=sizeof(struct Node);
static int nkeys;
static int *keys;
static int h;

void scan_tree(int nd);

void scan_tree(int nd) {
    if(lseek(h,nd*m,SEEK_SET)!=nd*m) return;
    if(read(h, &node, m)!=m) return;
    if(node.left_idx !=0) scan_tree(node.left_idx);
    if(node.right_idx!=0) scan_tree(node.right_idx);
    keys[nkeys++]=node.key;
}

int main(int argc, char **argv)
{
    int fsize;
    char fn[80]="main.dat";
    if(argc==2) {
        sscanf(argv[1],"%s",fn);
    }
    h=open(fn, O_WRONLY|O_CREAT|O_TRUNC, 0660);
    nkeys=0;
    while(1) {
        if(scanf("%d%d%d", &node.key, &node.left_idx, &node.right_idx)!=3) {
            break;
        } else {
            if(write(h, &node, m)!=m) return(-1);
            nkeys++;
        }
    }
    close(h);
    return(0);
}
