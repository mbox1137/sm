#include <stdio.h>

unsigned satsum(unsigned a1, unsigned a2);

int main(int argc, char **argv) {
    unsigned a1, a2, a;
    scanf("%u%u",&a1,&a2);
    a=satsum(a1,a2);
    printf("%u+%u=%u\n",a1,a2,a);
    return(0);
}
