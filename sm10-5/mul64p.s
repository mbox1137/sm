
	.code32

	.data

out_format:	.asciz	"%c"
nl_format:	.asciz	"\n"

	.text

	.globl  mul64p
	.type   mul64p, @function

	.equ    A, 4*2
	.equ    B, A+8

//__m128 mul64p(u_int64_t a, u_int64_t b);
mul64p:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%edi
	andl	$0xfffffff0, %esp
	subl	$0x10, %esp
	movl	%esp, %esi
//https://stackoverflow.com/questions/17863411/sse-multiplication-of-2-64-bit-integers
//ab * cd
	movq	A(%ebp), %xmm1	/* .. ab */
	movq	B(%ebp), %xmm2	/* .. cd */
	movdqa	%xmm1, %xmm3	/* .. ab */
	movdqa	%xmm2, %xmm4	/* .. cd */
//11 01 10 00 : xmm0.{3,2,1,0} == xmm0.{3,1,2,0}
	shufps	$0xD8, %xmm3, %xmm3	/* .a.b */
	shufps	$0xD8, %xmm4, %xmm4	/* .c.d */
//a*c b*d
	PMULUDQ	%xmm3, %xmm4	/* a*c b*d */
	movdqa	%xmm4, %xmm6	/* a*c b*d */

	movdqa	%xmm1, %xmm3	/*..ab*/
	movdqa	%xmm2, %xmm4	/*..cd*/
//11 01 10 00 : xmm0.{3,2,1,0} == xmm0.{3,1,2,0}
	shufps	$0xD8, %xmm3, %xmm3	/*.a.b*/
//11 00 10 01 : xmm0.{3,2,1,0} == xmm0.{3,0,2,1}
	shufps	$0xC9, %xmm4, %xmm4	/*.d.c*/
//
	PMULUDQ	%xmm3, %xmm4	/* a*d b*c */
	movdqa	%xmm4, %xmm5
	PSRLDQ	$8, %xmm5	/* 00 a*d */
	PSLLDQ	$8, %xmm4	/* b*c 00 */
	PSRLDQ	$8, %xmm4	/* 00 b*c */
	PADDQ	%xmm4, %xmm5	/* 00 a*d+b*c ????????????????*/
	PSLLDQ	$4, %xmm5	/* 0 a*d+b*c 0 */

	

	xor	%ecx, %ecx
	movdqa	%xmm0, %xmm1
m1:
	MOVDQA  %xmm1, (%esi)
	mov	(%esi), %ah
	PSRLDQ	$1, %xmm1
	mov	  (%esi), %edx
	or	 4(%esi), %edx
	or	 8(%esi), %edx
	or	12(%esi), %edx
	jz	m2
	mov	%ah, %al
	and	$0xF, %al
	push	%eax
	inc	%ecx
	mov	%ah, %al
	shr	$4, %al
	push	%eax
	inc	%ecx
	jmp	m1
m2:
	MOVDQA  %xmm0, (%esi)
m5:
	pop	%eax
	dec	%ecx
	cmp	$0, %al
	jz	m5
	push	%eax
	inc	%ecx
m3:
	pop	%eax
	and	$0xF, %al
	add	$'0', %al
	cmp	$'9', %al
	jbe	m4
	add	$'a'-'0'-10, %al
m4:
	push	%esi
	push	%ecx
	push	%eax
	push	$out_format
	call	printf
	add	$4*2, %esp
	pop	%ecx
	pop	%esi
	loop	m3

	push	%esi
	push	$nl_format
	call	printf
	add	$4*1, %esp
	pop	%esi
	MOVDQA  (%esi), %xmm0
m9:
	mov     %ebp, %eax
	sub	$4*2, %eax
	mov	%eax, %esp
	popl	%edi
	popl	%esi
	mov     %ebp, %esp
	pop     %ebp
	ret
