	.code32

	.data
input_format:
	.string "%u %u"
output_format:
	.string "%u\n"

	.bss
num1:
	.space	4
num2:
	.space	4
sum:
	.space	4

	.text
	.globl	main
	.type	main, @function

main:

satsum:
	pushl	$num2
	pushl	$num1
	pushl	$input_format
	call	scanf
	addl	$4*3, %esp
	movl	(num1), %eax
	addl	(num2), %eax
	movl	%eax, (sum)
	//jno	Display

	movl	(num1), %ebx
	cmp	%ebx, %eax
	jl	overf

	movl	(num2), %ebx
	cmp	%ebx, %eax
	jl	overf

overf:
	rcr	$1, %eax
	sar	$16, %eax
	sar	$16, %eax

Display:
	pushl	%eax
	pushl	$output_format
	call	printf
	popl	%eax
	popl	%ecx

Return:
	xorl	%eax, %eax
	ret
