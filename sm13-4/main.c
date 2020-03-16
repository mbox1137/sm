#include <stdio.h>
#include "perms_to_str.h"

#define NBUF 80

int main(int argc, char **argv)
{
    int n,perm;
    char buf[NBUF];
    if(argc==3)
    {
        sscanf(argv[1],"%i",&n);
        sscanf(argv[2],"%i",&perm);
    } else
        printf("./main 3 0640\n");
    perms_to_str(buf,n,perm);
    printf("%d 0%o:\t%s\n",n,perm,buf);
    return(0);
}
