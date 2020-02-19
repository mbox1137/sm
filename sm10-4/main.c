#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

float dotProduct(int n, float *x, float *y);

int main(int argc, char **argv) {
    int k, n;
    float *x, *y, dp, dp0;

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
    if(y==NULL) {
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
    dp0=0.0;
    for(k=0; k<n; k++) {
        dp0+=x[k]*y[k];
    }
    dp=dotProduct(n, x, y);
    printf("dp0=%g dp=%g\n",dp0,dp);
    free(y);
    free(x);
    return(0);
}
