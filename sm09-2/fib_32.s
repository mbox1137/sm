	.code32

	.data
input_format:
	.string "%d%d"

	.bss
A:
	.space	4
B:
	.space	4

	.text
	.globl	main
	.type	main, @function
	.globl	A, B

main:
	push	%ebx

GetInput:
	pushl	$B
	pushl	$A
	pushl	$input_format
	call	scanf
	addl	$4*3, %esp

Display:
	call	print_fib

Return:
	pop	%ebx
	xorl	%eax, %eax
	ret
