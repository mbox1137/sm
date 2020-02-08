	.code32

	.text
	.globl	satsum
	.type	satsum, @function

//unsigned satsum(unsigned a1, unsigned a2);
satsum:
	push	%ebp
	mov	%esp, %ebp

	xor	%eax, %eax

	mov	%ebp, %esp
	pop	%ebp
	ret
