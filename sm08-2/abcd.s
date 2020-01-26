/*
https://ru.wikibooks.org/wiki/%D0%90%D1%81%D1%81%D0%B5%D0%BC%D0%B1%D0%BB%D0%B5%D1%80_%D0%B2_Linux_%D0%B4%D0%BB%D1%8F_%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D0%B8%D1%81%D1%82%D0%BE%D0%B2_C
https://forum.nasm.us/index.php?topic=1514.msg6228#msg6228
https://stackoverflow.com/questions/38335212/calling-printf-in-x86-64-using-gnu-assembler
https://www.opennet.ru/docs/RUS/gas/gas-7.html
$ gcc -m32 -c -o aplusb.o aplusb.s
$ gcc -m32 -o aplusb aplusb.o
$ echo 123|./aplusb
The number+1 is 124
*/

		.code64

	.include "abcd.inc"

.data
input_format:	.ascii "%d %d %d %d\0"
output_format:	.ascii "%ld*%ld + %ld*%ld = %ld\n\0"

.bss
a:	.space	4
b:	.space	4
c:	.space	4
d:	.space	4
r:	.space	4

.text

process:
	push	%rbx
	movl	a(%rip), %eax
	mull	b(%rip)
	movl	%eax, %ebx
	movl	c(%rip), %eax
	mull	d(%rip)
	addl	%ebx, %eax
	pop	%rbx
        ret

.globl  main
.type   main, @function

/*
https://en.wikipedia.org/wiki/X86_calling_conventions
RDI, RSI, RDX, RCX, R8, R9
*/

main:
	push	%rbx

GetInput:
	lea	input_format(%rip), %rdi
	lea	a(%rip), %rsi
	lea	b(%rip), %rdx
	lea	c(%rip), %rcx
	lea	d(%rip), %R8
	call	scanf

Calculate:
	call	process
	movl	%eax, (r)

Display:	//http://www.cyberforum.ru/post12481559.html
	lea	output_format(%rip), %rdi
	mover	(a), %rsi
	mover	(b), %rdx
	mover	(c), %rcx
	mover	(d), %R8
	mover	(r), %R9
        call	printf

Return:
	pop	%rbx
        ret

        .size   main, . - main    /* размер функции main */
