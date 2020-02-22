
	.code32

	.text

	.globl	mul64r
	.type	mul64r, @function

	.equ	A, 4*2
	.equ	B, A+8
	.equ	T, -16

//__m128 mul64r(u_int64_t a, u_int64_t b);
mul64r:
	push	%ebp
	mov	%esp, %ebp
	sub	16, %esp
/*
	mov	A(%ebp), %rax
	mulq	B(%ebp)

	mov	%rax, T(%ebp)
	mov	%rdx, T+8(%ebp)
	MOVDQU	T(%ebp), %xmm0
*/
m9:
	mov	%ebp, %esp
	pop	%ebp
	ret
