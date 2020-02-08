	.code32

	.bss
A:
	.space	4
B:
	.space	4
C:
	.space	4
D:
	.space	4
R:
	.space	4

	.text
	.globl	process
	.type	process, @function
	.globl	A, B, C, D, R

process:
	movl	(A), %edi
	movl	(B), %esi
	movl	(C), %edx
	movl	(D), %ecx

	pushl	%ebx
	movl	%edx, %eax
	imull	%ecx
	movl	%eax, %ebx
	movl	%edi, %eax
	imull	%esi
	subl	%ebx, %eax
	pop	%ebx

	movl	%eax, (R)
	xorl	%eax, %eax
	ret
