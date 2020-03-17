#include <stdio.h>
int forward_args (int v2, long long v3, float v4);

int process(int *that, long long v2, float v4, unsigned v3) {
    printf("%lld\n", v2);
    printf("%f\n", v4);
    printf("%u\n", v3);
    return 1;
}

int main() {
    int v2 = 2;
    long long v3 = 4;
    float v4 = 1.0;
    printf("%d\n", forward_args(v2, v3, v4));

    return 0;
}
