//https://gamedev.ru/code/articles/?id=4238&page=5

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

	mov	X(%ebp), %esi
	mov	Y(%ebp), %edi

	movups	(%esi), %xmm0
	movups	(%edi), %xmm1
	mulps	%xmm1, %xmm0
//01 00 11 10
	shufps	$0x4E, %xmm0, %xmm1
	addps	%xmm1, %xmm0
//10 00 01 01
	shufps	$0x85, %xmm0, %xmm1
	addps	%xmm1, %xmm0

	movss   %xmm0, TMP(%ebp)
	fld	TMP(%ebp)
m9:
	pop	%edi
	pop	%esi
	mov     %ebp, %esp
	pop     %ebp
	ret
