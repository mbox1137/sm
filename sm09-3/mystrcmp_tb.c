#include <stdio.h>
#include <string.h>

int mystrcmp(const char *str1, const char *str2);

int main(int argc, char **argv) {
    int a, b;
    if(argc == 3) {
        a=mystrcmp(argv[1], argv[2]);
        b=strcmp(argv[1], argv[2]);
        printf("mystrcmp(%s,%s)\t=%d\t(%d)\n",argv[1],argv[2],a,b);
    }
    return(0);
}
