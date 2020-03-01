#include <stdio.h>

int mygetchar(void)
{
    int ic=0;
    asm(
    "	mov	$3, %%eax	\n\t"
    "	mov	$0, %%ebx	\n\t"
    "	lea	%1, %%ecx	\n\t"
    "	mov	$1, %%edx	\n\t"
    "	int	$0x80		\n\t"
    "	cmp	$1, %%eax	\n\t"
    "	je	mm1		\n\t"
    "	xor	%%eax, %%eax	\n\t"
    "	dec	%%eax		\n\t"
    "	mov	%%eax, %0	\n\t"
    "mm1:			"
        :"=m"(ic)
        :"m"(ic)
        :"eax","ebx","ecx","edx");

    return(ic);
}

void myputchar(int ic)
{
    asm(
    "	mov	$4, %%eax	\n\t"
    "	mov	$1, %%ebx	\n\t"
    "	lea	%1, %%ecx	\n\t"
    "	mov	$1, %%edx	\n\t"
    "	int	$0x80		    "
        :"=m"(ic)
        :"m"(ic)
        :"eax","ebx","ecx","edx");

    return;
}

void myexit(int ret_val)
{
    asm(
    "	movl	$1, %%eax	\n\t"
    "	movl	%1, %%ebx	\n\t"
    "	int	$0x80		    "
        :"=m"(ret_val)
        :"m"(ret_val)
        :"eax","ebx");

    return;
}

int main(int argc, char **argv)
{
    int ic;
    unsigned char cm = 'A' ^ 'a';
    while(1)
    {
        ic=mygetchar();
        if(ic==EOF)
            break;
        if(ic>='a' && ic<='z')
            ic&=~cm;
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
