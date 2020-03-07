#include <stdio.h>
#include "lnwf.h"

//Проверка

extern struct FileWriteState *stout;

int main(int argc, char **argv)
{
    int n;
    n='A';

    if(argc>1) {
        sscanf(argv[1],"%i",&n);
    }
    printf("n=%d\n",n);
/*
    writechar(n, stout);
    writechar('\n', stout);
    flush(stout);
*/
    writeu32_(n);
    writechar('\n', stout);
    flush(stout);

    return(0);
}
