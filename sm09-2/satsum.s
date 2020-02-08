	.code32

	.text
	.globl	satsum
	.type	satsum, @function

	.equ	A1, 4*2
	.equ	A2, 4*3

//unsigned satsum(unsigned a1, unsigned a2);
satsum:
	push	%ebp
	mov	%esp, %ebp

	mov	A1(%ebp), %eax
	add	A2(%ebp), %eax
//	xor	%eax, %eax

	mov	%ebp, %esp
	pop	%ebp
	ret
