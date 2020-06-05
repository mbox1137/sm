#include <stdio.h>
#include <malloc.h>
#include "run.h"

int main(int argc, char** argv) {
    char cmd[]="bc";
    char inp[]="2+2*2";
    char* out;
    char* err;
    int rv;
    int tout;

    tout=1000;
    printf("cmd=%s\n",cmd);
    printf("inp=%s\n",inp);
    rv=run(cmd, inp, &out, &err, tout);
    printf("rv=%d\n",rv);
    printf("out=%s\n",out);
    printf("err=%s\n",out);
    free(out);
    free(err);
    return(rv);
}
