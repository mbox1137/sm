#include <stdio.h>
#include "lnwf.h"

//Проверка

extern struct FileWriteState *stout;
void writeu32_(int);

int main(int argc, char **argv)
{
    int n;
    n=123;

    if(argc>1) {
        sscanf(argv[1],"%i",&n);
    }
    printf("n=%d\n",n);

    writeu32_(n);
    flush(stout);
    return(0);
}
