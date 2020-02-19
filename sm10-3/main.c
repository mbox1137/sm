#include <stdio.h>
#include <stdlib.h>
#include "tree_find.h"

static struct Node tmp[]={
    {1.1, NULL, NULL, "one"},
    {2.2, NULL, NULL, "two"},
    {3.3, NULL, NULL, "three"},
    {4.4, NULL, NULL, "four"},
    {5.5, NULL, NULL, "five"},
    {6.6, NULL, NULL, "six"},
    {7.7, NULL, NULL, "seven"},
    {8.8, NULL, NULL, "eight"},
    {9.9, NULL, NULL, "nine"},
    {10.0, NULL, NULL, "ten"},
    {11.1, NULL, NULL, "eleven"},
    {12.2, NULL, NULL, "twelve"}
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
    if((argc == 2) && (sscanf(argv[1],"%lf",&key)==1)) {
    } else {
        key=11.1;
    }

    str=nt;
    res=tree_findc(root, key, &str);
    printf("c: key=%lg res=%d str=%s\n",key,res,str);

    str=nt;
    res=tree_find(root, key, &str);
    printf("s: key=%lg res=%d str=%s\n",key,res,str);

    return(0);
}
