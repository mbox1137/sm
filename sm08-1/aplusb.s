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
output_format:	.ascii "The sum is %ld\n\0"
input_format:	.ascii "%ld %ld\0"
//end_of_format:	.ascii "\0\0"

.bss
num1:
	.space	8
num2:
	.space	8
res_of_sum:
	.space	8

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
	movq	%rax, (res_of_sum)

Display:
	//movb	$10, (end_of_format)
	lea	output_format(%rip), %rdi
	movq	(res_of_sum), %rsi
        call	printf

Return:
	pop	%rbx
        ret

        .size   main, . - main    /* размер функции main */
