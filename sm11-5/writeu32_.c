#include <stdio.h>
#include <unistd.h>
#include "lnwf.h"

void writeu32_(int n)
{
    int tmp;
    asm(
    "   call	writeu32"
        :"=a"(tmp)
        :"c"(n)
    );
    return;
}
