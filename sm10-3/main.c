#include <stdio.h>
//echo 5 12 |./main

double tree_find(double x, double y);

int main(int argc, char **argv) {
    double x, y, r;
    if(scanf("%lf%lf",&x, &y)!=2) {
        x=4.0;
        y=3.0;
    }
    r=tree_find(x, y);
    printf("vlen(%lf,%lf)=%lf\n",x,y,r);
    return(0);
}
