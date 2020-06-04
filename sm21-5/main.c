#include <stdio.h>
#include <malloc.h>
#include "run.h"

int main(int argc, char** argv) {
    char cmd[]="1";
    char inp[]="2";
    char* out;
    char* err;
    int rv;
    int tout;

    tout=1000;
    rv=run(cmd, inp, &out, &err, tout);
    free(out);
    free(err);
    return(rv);
}
