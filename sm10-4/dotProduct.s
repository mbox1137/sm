	.code32

	.data

	.text
	.globl  dotProduct
	.type   dotProduct, @function

	.equ    N, 4*2
	.equ    X, N+4
	.equ    Y, X+4
	.equ    TMP, -4*1

//float dotProduct(int n, float *x, float *y);
dotProduct:
	push    %ebp
	mov     %esp, %ebp
	sub     $4*1, %esp	/* tmp */
	push	%esi
	push	%edi
/*
	movss   X(%ebp), %xmm0
	movss   %xmm0, %xmm1
	mulss	%xmm1, %xmm0

	movss   Y(%ebp), %xmm2
	movss   %xmm2, %xmm3
	mulss	%xmm3, %xmm2

	addss	%xmm0, %xmm2
	sqrtss	%xmm2, %xmm0
*/
	movss   %xmm0, TMP(%ebp)
	fld	TMP(%ebp)

m9:
	pop	%edi
	pop	%esi
	mov     %ebp, %esp
	pop     %ebp
	ret
