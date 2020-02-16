#include <stdio.h>
#include <stdlib.h>
#include "tree_find.h"

static struct Node tmp[]={
    {1.2, NULL, NULL, "one"},
    {2.3, NULL, NULL, "two"},
    {3.4, NULL, NULL, "three"}
};
static struct Node *root;

int main(int argc, char **argv) {
    struct Node *node;
    int res,k,n;
    double key;
    char *str, *nt="Nothing";
    n=sizeof(tmp)/sizeof(struct Node);
    for(k=0; k<n; k++) {
        if(k>0) {
            tmp[k].left=&tmp[k-1];
        }
        if(k<n-1) {
            tmp[k].right=&tmp[k+1];
        }
    }
    root=&tmp[0];
    key=2.3;

    str=nt;
    res=tree_findc(root, key, &str);
    printf("c: key=%lf res=%d str=%s\n",key,res,str);

    str=nt;
    res=tree_find(root, key, &str);
    printf("s: key=%lf res=%d str=%s\n",key,res,str);

    return(0);
}
