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
    char *str="Noting";
    n=sizeof(tmp)/sizeof(struct Node);
//    printf("n=%d\n",n);
    for(k=0; k<n; k++) {
//        printf("k=%d\n",k);
        if(k>0) {
            tmp[k].left=&tmp[k-1];
        }
        if(k<n-1) {
            tmp[k].right=&tmp[k+1];
        }
    }
    root=&tmp[0];
    key=2.3;
/*
    node=root;
    printf("%lf %p %p %s\n",
        node->key,node->left,node->right,node->str);
    node=node->right;
    printf("%lf %p %p %s\n",
        node->key,node->left,node->right,node->str);
*/
    res=tree_findc(root, key, &str);
    printf("key=%lf res=%d str=%s\n",key,res,str);
    return(0);
}
