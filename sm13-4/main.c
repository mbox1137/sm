#include <stdio.h>
#include "perms_to_str.h"

int main(int argc, char **argv)
{
    int n,perm;
    if(argc==3)
    {
        sscanf(argv[1],"%i",&n);
        sscanf(argv[2],"%i",&perm);
    } else
        printf("./main 3 0640\n");
    printf("%d 0%o\n",n,perm);
    return(0);
}
