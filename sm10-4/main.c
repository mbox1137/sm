#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

float dotProduct(int n, float *x, float *y);

int main(int argc, char **argv) {
    int k, n, nn, kk, kkn;
    float *x, *y, dp, dp0;

//    fprintf(stderr,"[echo 1.1, 2.2, 3.3, 4.4 5.5, 6.6, 7.7, 8.8 |] ./main [4]\n");
    if(argc>1) {
        if(sscanf(argv[1],"%d",&n)!=1) {
            fprintf(stderr,"Invalid n\n");
            return(-1);
        }
    } else {
        n=5;
    }
    nn=n;
    n=abs(n);
/*
http://www.ccfit.nsu.ru/~kireev/lab4/lab4intr.htm
     float *x; // массив для обработки с помощью SSE
     x=(float)_mm_malloc(N*sizeof(float),16);
     // : здесь обработка :
     _mm_free(x);
 */
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
    if(argc>1 && nn>0) {
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
    } else {
        for(k=0; k<n; k++) {
            kk=k+1;
            kkn=kk+n;
            x[k]=kk+kk/10.0;
            y[k]=kkn+kkn/10.0;
        }
    }
    for(k=0; k<n; k++) {
        printf("\t%g",x[k]);
    }
    printf("\n");
    for(k=0; k<n; k++) {
        printf("\t%g",y[k]);
    }
    printf("\n");
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
