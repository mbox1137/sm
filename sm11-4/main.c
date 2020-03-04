#include <stdio.h>
#include "lnwf.h"

//Проверка

extern struct FileWriteState *stout;

int main(int argc, char **argv)
{
    int ic;
    while(1)
    {
        ic=nextchar();
        if(ic==EOF)
            break;
        writechar(ic, stout);
//        myputchar(ic);
    }
    flush(stout);
    return(0);
}

void _start(void)
{
    int retval;
    retval=main(0,0);
    myexit(retval);
}
