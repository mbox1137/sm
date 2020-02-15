#include <stdlib.h>
#include <math.h>
#include "tree_find.h"

int tree_findc(struct Node *root, double key, char **pstr) {
    struct Node *node;
    for(node=root; node!=NULL; node=node->right) {
/*
        if(fabs((node->key) - key)<1E-8) {
            if(pstr!=NULL) {
//                *pstr=node->str;
                }
            return(1);
        }
*/
    }
    return(0);
}
