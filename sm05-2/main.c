#include <stdio.h>
#include "norm_path.h"
#include <string.h>

int main(int argc, char *argv[])
{
    char *str = argv[1];
    char str2[80];
    strcpy(str2, str);

//    printf("str = %s\n", argv[1]);

    ans(str);
    normalize_path(str2);

    printf("ans = %s\n", str);
    printf("my  = %s\n", str2);

    return 0;
}

