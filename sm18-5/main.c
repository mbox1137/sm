#define DEBUG 0

#include <stdio.h>
#include <string.h>
#include "solution.h"
#include "addname.h"

int main(int argc, char *argv[])
{
    int retval;
#if DEBUG
    if(argc==1) {
        fprintf(stderr,"%s cmd1 cmd2 cmd3 ...\n", argv[0]);
        return(1);
    }
    retval=solution(argc-1, &argv[1]);
    printf("%d\n", retval);
#else
    retval=solution(argc-1, &argv[1]);
#endif
    return(retval);
}
