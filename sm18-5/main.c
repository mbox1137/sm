#define DEBUG 1

#include <stdio.h>
#include <string.h>
#include "solution.h"

int main(int argc, char *argv[])
{
    char *cmd, str[1000];
    char dummy[]=" 11111  222222   3333333 ";
//    cmd=NULL;
    cmd=dummy;
    if(argc == 2) {
        cmd=argv[1];
    } else if(argc!=1) {
        fprintf(stderr,"./main %s\n", cmd);
        return(1);
    }
    strcpy(str, cmd);
    printf("solution(\"%s\")=%d\n", cmd, solution(str));
}
