#define DEBUG 1

#include <stdio.h>
#include "mysys.h"

int main(int argc, char *argv[])
{
    char *cmd;

    cmd="ls -la";
    if(argc == 2) {
        cmd=argv[1];
    } else if(argc!=1) {
        fprintf(stderr,"./main %s\n", cmd);
        return(1);
    }
    mysys(cmd);
}
