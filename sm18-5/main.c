#define DEBUG 0

#include <stdio.h>
#include <string.h>
#include "solution.h"
#include "addname.h"

int main(int argc, char *argv[])
{
#if DEBUG
    if(argc==1) {
        fprintf(stderr,"%s cmd1 cmd2 cmd3 ...\n", argv[0]);
        return(1);
    }
    printf("%d\n", solution(argc-1, &argv[1]));
#else
    solution(argc-1, &argv[1]);
#endif
}
