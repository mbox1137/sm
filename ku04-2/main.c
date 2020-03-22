#include <stdio.h>
#include <stdint.h>
#include "process.h"

int main(int argc, char **argv) {
    int32_t res;
    struct S s;
    int hn;
    if(argc == 5) {
     sscanf(argv[1],"%d",&s.z[0]);
     sscanf(argv[2],"%d",&s.z[1]);
     sscanf(argv[3],"%d",&s.y[0]);
     sscanf(argv[4],"%d",&s.y[1]);
    } else {
     s.z[0]=2147483647;
     s.z[1]=2147483647;
     s.y[0]=8;
     s.y[1]=9;
    }
    res=process(&s);

//long long t = (long long) p->z[0] * (long long) p->y[1] + (long long) p->z[1] * (long long) p->y[0];

    hn=16;
    printf("(%d*%d+%d*%d)/%d=%lld",
       s.z[0],s.y[1] , s.z[1],s.y[0], hn,
       ((int64_t)s.z[0] * (int64_t)s.y[1] + 
       (int64_t)s.z[1] * (int64_t)s.y[0]) / 
       (int64_t)hn );
    printf("(%u:%d)",res,res);
    printf("\n");
    return 0;
}
