#include <stdio.h>
#include "func.h"

int process(int *that, long long v2, float v4, unsigned v3) {
    printf("%lld\n", v2);
    printf("%f\n", v4);
    printf("%u\n", v3);
    return 1;
}
