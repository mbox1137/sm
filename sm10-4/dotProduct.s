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
//01 00 11 10
	shufps	$0x4E, %xmm0, %xmm1
/*
 1.1 2.2 3.3 4.4
 1.1 2.2 3.3 4.4
 0 0 1.1 2.2
*/
	addps	%xmm1, %xmm0
/*
 1.1 2.2 3.3 4.4
 1.1 2.2 4.4 6.6
 0 0 1.1 2.2
*/
//01 00 00 01
	shufps	$0x41, %xmm0, %xmm1

/*
//1101 1100
	shufps	$0xDC, %xmm1, %xmm0
	addps	%xmm0, %xmm1
*/
	movups	%xmm0, (%esi)
	movups	%xmm1, (%edi)

	movss   %xmm0, TMP(%ebp)
	fld	TMP(%ebp)

m9:
	pop	%edi
	pop	%esi
	mov     %ebp, %esp
	pop     %ebp
	ret
