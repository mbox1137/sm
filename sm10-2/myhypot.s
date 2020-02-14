	.code32

	.data

	.text
	.globl  myhypot
	.type   myhypot, @function

	.equ    X, 4*2
	.equ    Y, 4*3
	.equ    TMP, -4*1

//float myhypot(float x, float y);
myhypot:
	push    %ebp
	mov     %esp, %ebp
	sub     $4*1, %esp

	movss   X(%ebp), %xmm0
	movss   %xmm0, %xmm1
	mulss	%xmm1, %xmm0

	movss   Y(%ebp), %xmm2
	movss   %xmm2, %xmm3
	mulss	%xmm3, %xmm2

	addss	%xmm0, %xmm2
	sqrtss	%xmm2, %xmm0

	movss   %xmm0, TMP(%ebp)
	fld	TMP(%ebp)

m9:
	mov     %ebp, %esp
	pop     %ebp
	ret
