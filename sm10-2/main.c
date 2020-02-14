#include <stdio.h>
//echo 5 12 |./main

float myhypot(float x, float y);

int main(int argc, char **argv) {
    float x, y, r;
    if(scanf("%f%f",&x, &y)!=2) {
        x=4.0;
        y=3.0;
    }
    r=myhypot(x, y);
    printf("vlen(%f,%f)=%f\n",x,y,r);
    return(0);
}
