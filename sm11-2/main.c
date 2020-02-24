#include <stdio.h>

#define C 0

int mygetchar(void);

int mygetchar(void) {
    int ic;
    register int ecx asm ("ecx");
/*
	movl	$3, %eax	//# номер сист. вызова read
	movl	$0, %ebx	//# параметр 1: дескриптор стандартного ввода
	movl	$ic, %ecx	//# параметр 2: адрес буфера (он же - фактический 
	     			//# параметр макровызова)
	movl	$1, %edx	//# параметр 3: количество байтов для чтения
	int	$0x80		//# выполнить системный вызов

	cmp	-1, %eax"
	jne	m1"
	mov	%eax, %ic"
m1:
*/
    ic=0;
    __asm__ volatile ( "movl	%1, %0" : "=r" (ecx) : "m" (ic) );
    ic--;
    __asm__ volatile ( "movl	%1, %0" : "=m" (ic)   : "r" (ecx) );
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
        printf("ic=%d\n", ic);
        return(-1);
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
