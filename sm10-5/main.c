#include <xmmintrin.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>


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
    a=0xCAFEBABE;
    b=0xDEADBEEF;
    printf(" %llx",a);
    printf(" %llx",b);
    printf("\n");
    printf("a=%lld b=%lld\n",a,b);
    u.v=mul64p(a,b);
    for(k=0; k<16; k++) {
        printf(" %x",u.c[k]);
    }
    printf("\n");
    u.v=mul64r(a,b);
    for(k=0; k<16; k++) {
        printf(" %x",u.c[k]);
    }
    printf("\n");
    return(0);
}
