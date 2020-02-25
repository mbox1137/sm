#include <stdio.h>

#define C 0

int mygetchar(void);

int mygetchar(void) {
    int ic, *ica;
    ica=&ic;
__asm__ volatile (
	"movl	$3, %eax\n\t"	//# номер сист. вызова read
	"movl	$0, %ebx\n\t"	//# параметр 1: дескриптор стандартного ввода
	"movl	%ica, %ecx\n\t" //# параметр 2: адрес буфера
	"movl	$1, %edx\n\t"	//# параметр 3: количество байтов для чтения
	"int	$0x80\n\t"	//# выполнить системный вызов
	"cmp	$-1, %eax\n\t"
	"jne	m1\n\t"
	"mov	%eax, %ic\n\t"
"m1:\n\t"
);
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
