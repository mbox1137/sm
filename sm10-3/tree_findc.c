#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tree_find.h"
#include <math.h>

int tree_findc(struct Node *root, double key, char **pstr) {
    struct Node *node;
    for(node=root; node->left!=NULL; node=node->left) ;
    for(; node!=NULL; node=node->right) {
//        printf("\t%lg\n",node->key);
        if(
           (isnan(node->key) && isnan(key)) ||
            node->key == key ||
            fabs((node->key) + key)/2.0 < 1E-8 && 
            fabs((node->key) - key) < 1E-8 ||
            fabs(2.0 * (node->key - key) / (node->key + key)) < 1E-8
        ) {
            if(pstr!=NULL) {
                *pstr=node->str;
                }
            return(1);
        }
    }
    return(0);
}
