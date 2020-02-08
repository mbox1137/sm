/*
 $ make
as -c --32 -o print-rev-n-1.o print-rev-n-1.s
gcc -m32 -no-pie -o print-rev-n-1 print-rev-n-1.o
 $ echo 5 |./print-rev-n-1
5
4
3
2
1
0
*/

		.code32

.data
input_format:	.string "%d"
output_format:	.string "%d\n"

.bss
num:	.space	4

.text

.globl  main
.type   main, @function

main:

GetInput:
	pushl	$num
	pushl	$input_format
	call	scanf
	addl	$8, %esp

Calculate:
	movl	(num), %ecx

Display:
//	cmpl	$0s, %ecx
	xorl	%eax, %eax
	cmpl	%eax, %ecx
	jl	m2
m1:
	pushl	%ecx
	pushl	$output_format
	call	printf
	popl	%eax
	popl	%ecx

	loopl	m1

	pushl	%ecx
	pushl	$output_format
	call	printf
	popl	%eax
	popl	%ecx
m2:

Return:
	ret

        .size   main, . - main    /* размер функции main */
