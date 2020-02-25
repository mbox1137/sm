#include <stdio.h>

#define C 0

int mygetchar(void);

int mygetchar(void) {
    int ic, *ica=&ic;
    ic=0;
asm(
"	movl	$3, %%eax	\n\t"
"	movl	$0, %%ebx	\n\t"
"	movl	%1, %%ecx	\n\t"
"	movl	$1, %%edx	\n\t"
"	int	$0x80		\n\t"
"	cmp	$1, %%eax	\n\t"
"	je	m1		\n\t"
"	xor	%%eax, %%eax	\n\t"
"	dec	%%eax		\n\t"
"	mov	%%eax, %0	\n\t"
"m1:				    "
    :"=m"(ic)
    :"m"(ica)
    :"eax","ebx","ecx","edx");
    return(ic);
}

int main(int argc, char **argv) {
    int ic;
    unsigned char cm = 'A' ^ 'a';
    while(1) {
#if C
        ic=getchar();
#else
        ic=mygetchar();
#endif
        if(ic==EOF) {
            break;
        }
        if(ic>='a' && ic<='z')
            ic&=~cm;
        putchar(ic);
    }
    return(0);
}
