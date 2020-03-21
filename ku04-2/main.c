#include <stdio.h>
#include <stdint.h>
#include "process.h"

int main(int argc, char **argv) {
    uint32_t res;
    struct S s;
    if(argc == 5) {
     sscanf(argv[1],"%d",&s.z[0]);
     sscanf(argv[2],"%d",&s.z[1]);
     sscanf(argv[3],"%d",&s.y[0]);
     sscanf(argv[4],"%d",&s.y[1]);
    } else {
     s.z[0]=3;
     s.z[1]=4;
     s.y[0]=5;
     s.y[1]=6;
    }
    res=process(&s);
    printf("%d*%d+%d*%d=%lld(%d)\n", 
               s.z[0],s.y[1] , s.z[1],s.y[0],
     (uint64_t)s.z[0]*s.y[1] + s.z[1]*s.y[0],
               res);
    return 0;
}
