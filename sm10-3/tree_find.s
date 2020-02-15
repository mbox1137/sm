//https://ru.bmstu.wiki/SSE2_(Streaming_SIMD_Extensions_2)

	.code32

	.data

	.text
	.globl  tree_find
	.type	tree_find, @function

	.equ    X, 4*2
	.equ    Y, 4*2+8*1
	.equ    TMP, -8*1

//float myhypot(float x, float y);
tree_find:
	push    %ebp
	mov     %esp, %ebp
	sub     $8*1, %esp

	movsd   X(%ebp), %xmm0

	movsd   %xmm0, %xmm1
	mulsd	%xmm1, %xmm0

	movsd   Y(%ebp), %xmm2
	movsd   %xmm2, %xmm3
	mulsd	%xmm3, %xmm2

	addsd	%xmm0, %xmm2
	sqrtsd	%xmm2, %xmm0

	movsd   %xmm0, TMP(%ebp)
	fldl	TMP(%ebp)

m9:
	mov     %ebp, %esp
	pop     %ebp
	ret
