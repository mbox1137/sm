
	.code32

	.text

	.globl  mul64p
	.type   mul64p, @function
	.globl  dp
	.type   dp, @function

	.equ    A, 4*2
	.equ    B, A+8

//__m128 mul64p(u_int64_t a, u_int64_t b);
mul64p:
	push    %ebp
	mov     %esp, %ebp

	movq	A(%ebp), %xmm0
	movq	B(%ebp), %xmm1
/*
//01 00 11 10
	shufps	$0x4E, %xmm0, %xmm1
//10 00 01 01
	shufps	$0x85, %xmm0, %xmm1

//00 01 10 11 : xmm0.{3,2,1,0} == xmm0.{0,1,2,3}
	shufps	$0x1B, %xmm0, %xmm0
*/
/*
	movss	(%esi), %xmm0
	mulss	(%edi), %xmm0
	movss   %xmm2, TMP(%ebp)
	fld	TMP(%ebp)
*/
m9:
	mov     %ebp, %esp
	pop     %ebp
	ret
