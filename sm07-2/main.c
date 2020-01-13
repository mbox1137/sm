#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

void process(size_t count, int *data, int *order);

int a1[]={5,4,3,2,1}; int r1[]={4,3,2,1,0};
int a2[]={5,3,3,2,1}; int r2[]={4,3,1,2,0};
const int n=5;
int r[n];

int vproc(size_t count, int *data, int *order, int *verification) {
    int k, res;
    char ch;
    res=0;
    for (k=0; k<count; k++) {
        if(order[k]==verification[k]) {
            ch=' ';
        } else {
            ch='*';
            res=-1;
        }
        printf("%c %d: %d -> %d (%d)\n",
            ch,k,data[k],order[k],verification[k]);
    }
    printf("\n");
    return(res);
}

int main()
{
    process(n,a1,r); vproc(n,a1,r,r1);
    process(n,a2,r); vproc(n,a2,r,r2);
    return 0;
}
