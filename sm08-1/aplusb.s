/*
https://ru.wikibooks.org/wiki/%D0%90%D1%81%D1%81%D0%B5%D0%BC%D0%B1%D0%BB%D0%B5%D1%80_%D0%B2_Linux_%D0%B4%D0%BB%D1%8F_%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D0%B8%D1%81%D1%82%D0%BE%D0%B2_C
https://forum.nasm.us/index.php?topic=1514.msg6228#msg6228
https://stackoverflow.com/questions/38335212/calling-printf-in-x86-64-using-gnu-assembler
$ gcc -m32 -c -o aplusb.o aplusb.s
$ gcc -m32 -o aplusb aplusb.o
$ echo 123|./aplusb
The number+1 is 124
*/

		.code64

.data
input_format:	.ascii "%ld %ld\n\0"
output_format:	.ascii "The sum is %ld\n\0"

.bss
num1:	.space	8
num2:	.space	8
sumnum:	.space	8

.text
.globl  main
.type   main, @function

main:
	push	%rbx

GetInput:
	lea	input_format(%rip), %rdi
	lea	num1(%rip), %rsi
	lea	num2(%rip), %rdx
	call	scanf

Calculate:
	movq	(num1), %rax
	addq	(num2), %rax
	movq	%rax, (sumnum)

Display:
	lea	output_format(%rip), %rdi
	movq	(sumnum), %rsi
        call	printf

Return:
	pop	%rbx
        ret

        .size   main, . - main    /* размер функции main */
