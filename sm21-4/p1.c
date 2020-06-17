#include <stdio.h>

void main() {
    int x;
    while(!feof(stdin)) {
        if(scanf("%d",&x)==1) {
            printf("%d\n", x+1);
        } else {
            fgetc(stdin);
        }
    }
}
