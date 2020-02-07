	.code32

	.data
input_format:	.ascii "%d %d %d %d\0"
output_format:	.ascii "%d\n\0"

	.text
	.globl	main
	.type	main, @function

main:
	push	%ebx

GetInput:
	pushl	$D
	pushl	$C
	pushl	$B
	pushl	$A
	pushl	$input_format
	call	scanf
	addl	$4*5, %esp

Calculate:
	call	process

Display:
	pushl	(R)
	pushl	$output_format
	call	printf
	addl	$4*2, %esp

Return:
	pop	%ebx
	ret

	.size	main, . - main
