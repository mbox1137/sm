#include <xmmintrin.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

__m128 mul64p(u_int64_t a, u_int64_t b);
__m128 mul64r(u_int64_t a, u_int64_t b);

typedef union {
    __m128 v;    // SSE 4 x float vector
    float a[4];  // scalar array of 4 floats
    unsigned char c[16];
} U;

int main(int argc, char **argv) {
    int k;
    u_int64_t a,b;
    __m128 c;
    U u;
    if( (argc==3) && 
        (sscanf(argv[1],"%lli",&a)==1) && 
        (sscanf(argv[2],"%lli",&b)==1) ) {
    } else {
        a=0xCAFEBABE; b=0xDEADBEEF;
    }

//    a=0xCAFEBABECAFEBABE; b=0xDEADBEEFDEADBEEF;
//    a=0x10000000000; b=0x10000000000;
    printf("a=%llx b=%llx\n",a,b);
    u.v=mul64p(a,b);
    for(k=0; k<16; k++) {
        if(u.c[15-k]!=0) {
            break;
        }
    }
    for(; k<16; k++) {
        printf("%02x",u.c[15-k]);
    }
    printf("\n");
/*
    u.v=mul64r(a,b);
    for(k=0; k<16; k++) {
        printf(" %x",u.c[k]);
    }
    printf("\n");
*/
    return(0);
}
