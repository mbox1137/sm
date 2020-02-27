#include <xmmintrin.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "u.h"

void print_xmm(U u) {
    unsigned char cc;
    int k;
    for(k=0; k<16; k++) {
        if(u.c[15-k]!=0) {
            break;
        }
    }
    cc=u.c[15-k++];
    printf("0x");
    if((cc&0xf0) == 0) {
        printf("%x",cc);
    } else {
        printf("%02x",cc);
    }
    for(; k<16; k++) {
        printf("%02x",u.c[15-k]);
    }
    printf("\n");
    return;
}

int main(int argc, char **argv) {
    u_int64_t a,b;
    U u, ab;
    if( (argc==3) && 
        (sscanf(argv[1],"%lli",&a)==1) && 
        (sscanf(argv[2],"%lli",&b)==1) ) {
    } else {
        a=0xCAFEBABE; b=0xDEADBEEF;
    }
    ab.v=mul64x64(a,b);
    u.v=mul64p(a,b);
    printf("%lld(%llx) * %lld(%llx)\n",a,a,b,b);
    print_xmm(u);
    return(0);
}
