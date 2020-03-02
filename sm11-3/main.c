#include <stdio.h>
#include "lnwf.h"

//Проверка

int main(int argc, char **argv)
{
    int ic;
    while(1)
    {
        ic=nextchar(stin);
        if(ic==EOF)
            break;
//        writechar(stout, ic);
        myputchar(ic);
    }
    return(0);
}

void _start(void)
{
    int retval;
    retval=main(0,0);
    myexit(retval);
}
