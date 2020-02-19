#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

float dotProduct(int n, float *x, float *y);

int main(int argc, char **argv) {
    int k, n;
    float *x, *y, dp;
    float xx[]={1.1, 2.2, 3.3, 4.4};
    float yy[]={5.5, 6.6, 7.7, 8.8};

    n=sizeof(xx)/sizeof(float);
    for(k=0; k<n; k++) {
        printf(" %g",xx[k]);
    }
    printf("\n");
    dp=dotProduct(n, xx, yy);
    n=sizeof(xx)/sizeof(float);
    for(k=0; k<n; k++) {
        printf(" %g",xx[k]);
    }
    printf("\n");
    n=sizeof(yy)/sizeof(float);
    for(k=0; k<n; k++) {
        printf(" %g",yy[k]);
    }
    printf("\n");
    return(0);

    if(scanf("%d",&n)!=1) {
        fprintf(stderr,"Invalid n\n");
        return(-1);
    }
    x=(float*)calloc(n, sizeof(float));
    if(x==NULL) {
        fprintf(stderr,"ivalid x=(float*)calloc(%d, %d)",n,sizeof(float));
        return(-1);
    }
    y=(float*)calloc(n, sizeof(float));
    if(x==NULL) {
        fprintf(stderr,"ivalid y=(float*)calloc(%d, %d)",n,sizeof(float));
        return(-1);
    }
    for(k=0; k<n; k++) {
        if(scanf("%f",&x[k])!=1) {
            fprintf(stderr,"Invalid x[%d]\n",k);
            return(-1);
        }
    }
    for(k=0; k<n; k++) {
        if(scanf("%f",&y[k])!=1) {
            fprintf(stderr,"Invalid y[%d]\n",k);
            return(-1);
        }
    }
//    dp=dotProduct(x, y);
    printf("dotProduct=%f\n",dp);
    free(y);
    free(x);
    return(0);
}
