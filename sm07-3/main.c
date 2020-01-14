#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "bsearch2.h"

static int a[]={1,2,3,40,50};
static const int n=sizeof(a)/sizeof(a[0]);

void vbs(size_t count, int *data, int x, struct BSearchResult bsr2) {
    int k;
    printf("{%d",data[0]);
    for (k=1; k<count; k++) {
        printf(", %d",data[k]);
    }
    printf("}: %d (%zu %zu %d)\n", x, bsr2.low, bsr2.hight, bsr2.result );
}

int cmpbsr2(const void *p1, const void *p2, void *user) {
    return(0);
}

int main()
{
    struct BSearchResult bsr2;
    int key=10;
    bsr2=bsearch2(&key,a,n,sizeof(a[0]),cmpbsr2,a);
    vbs(n,a,key,bsr2);
    return 0;
}
