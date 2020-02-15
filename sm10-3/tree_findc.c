#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tree_find.h"

int tree_findc(struct Node *root, double key, char **pstr) {
    struct Node *node;
    for(node=root; node!=NULL; node=node->right) {
/*
        printf("%lf %p %p %s\n",
            node->key,node->left,node->right,node->str);
*/
        if(fabs((node->key) - key)<1E-8) {
            if(pstr!=NULL) {
                *pstr=node->str;
                }
            return(1);
        }
    }
    return(0);
}
