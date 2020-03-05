#include <stdio.h>
#include <unistd.h>

void myputchar(int ic)
{
    asm volatile(
    "   int     $0x80               "
        :"=a"(ic)
        :"a"(4), "b"(1), "c"(ic), "d"(1)
    );
    return;
}

void myexit(int ret_val)
{
    asm(
    "   int     $0x80               "
        :"=a"(ret_val)
        :"a"(1), "b"(ret_val)
    );
    return;
}
