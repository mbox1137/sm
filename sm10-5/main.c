#include <xmmintrin.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

__m128 mul64p(u_int64_t a, u_int64_t b);

int main(int argc, char **argv) {
    u_int64_t a,b;
    __m128 c;
    a=0xCAFEBABE;
    b=0xDEADBEEF;
    printf("a=%lld b=%lld\n",a,b);
    mul64p(a,b);
    return(0);
}
