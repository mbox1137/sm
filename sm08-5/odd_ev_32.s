	.code32

	.data
input_format:
	.string "%d"
output_format:
	.string "%d\n%d\n"

	.bss
num:
	.space	4
sum_odd:
	.space	4
sum_ev:
	.space	4

	.text
	.globl  main
	.type   main, @function

main:

GetInput:
	xorl	%eax, %eax
	movl	%eax, (sum_odd)
	xorl	%eax, %eax
	movl	%eax, (sum_ev)
m1:
	pushl	$num
	pushl	$input_format
	call	scanf
	addl	$4*2, %esp
	cmp	$1, %eax
	jne	Display

	xorl	%ecx, %ecx
	xorl	$1, %ecx
	andl	(num), %ecx
	cmp	$1, %ecx
	je	m_odd
	jl	m_ev

m_odd:
	movl	(sum_odd), %eax
	addl	(num), %eax
	movl	%eax, (sum_odd)

	jno	m1

m_ev:
	movl	(sum_ev), %eax
	add	(num), %eax
	mov	%eax, (sum_ev)

	jno	m1

Display:
	pushl	$sum_odd
	pushl	$sum_ev
	pushl	$output_format
	call	printf
	add	$4*3, %esp

Return:
	xorl	%eax, %eax
	ret
