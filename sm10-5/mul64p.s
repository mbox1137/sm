
	.code32

	.data

out_format:	.asciz	"%c"
nl_format:	.asciz	"\n"

	.text

	.globl  mul64p
	.type   mul64p, @function
	.globl  qq

	.equ    A, 4*2
	.equ    B, A+8

//__m128 mul64p(u_int64_t a, u_int64_t b);
mul64p:
	push	%ebp
	movl	%esp, %ebp
	push	%esi
	push	%edi
	and	$0xfffffff0, %esp
	sub	$0x10, %esp
	mov	%esp, %esi
	sub	$0x10, %esp
	mov	%esp, %edi
//https://stackoverflow.com/questions/17863411/sse-multiplication-of-2-64-bit-integers
//ab * cd
	movq	A(%ebp), %xmm3	/* .. ab */
	movq	B(%ebp), %xmm4	/* .. cd */
//11 01 10 00 : xmm0.{3,2,1,0} == xmm0.{3,1,2,0}
	shufps	$0xD8, %xmm3, %xmm3	/* .a.b */
	shufps	$0xD8, %xmm4, %xmm4	/* .c.d */

	movdqa	%xmm3, %xmm0
	call	printxmm0
	movdqa	%xmm4, %xmm0
	call	printxmm0
//a*c b*d
	PMULUDQ	%xmm3, %xmm4	/* a*c b*d */
	movdqa	%xmm4, %xmm0
	call	printxmm0
	movdqa	%xmm4, %xmm6	/* a*c b*d */

	movq	A(%ebp), %xmm3	/* .. ab */
	movq	B(%ebp), %xmm4	/* .. cd */

	movdqa	%xmm3, %xmm0
	call	printxmm0
	movdqa	%xmm4, %xmm0
	call	printxmm0
//11 01 10 00 : xmm0.{3,2,1,0} == xmm0.{3,1,2,0}
	shufps	$0xD8, %xmm3, %xmm3	/*.a.b*/
//11 00 10 01 : xmm0.{3,2,1,0} == xmm0.{3,0,2,1}
	shufps	$0xC9, %xmm4, %xmm4	/*.d.c*/
	movdqa	%xmm3, %xmm0
	call	printxmm0
	movdqa	%xmm4, %xmm0
	call	printxmm0
//
	PMULUDQ	%xmm3, %xmm4	/* a*d b*c */
	movdqa	%xmm4, %xmm3	/* a*d b*c */
	movdqa	%xmm4, %xmm5
	movdqa	%xmm4, %xmm0
	call	printxmm0

	PSRLDQ	$8, %xmm5	/* 00 a*d */
	PSLLDQ	$4, %xmm5	/* 0 a*d 0	*/
	PSLLDQ	$8, %xmm4	/* b*c 00 */
	PSRLDQ	$8, %xmm4	/* 00 b*c */
	PSLLDQ	$4, %xmm4	/* 0 b*c 0	*/
	movdqa	%xmm5, %xmm0
	call	printxmm0
	movdqa	%xmm4, %xmm0
	call	printxmm0
qq:
	MOVDQA  %xmm6, (%esi)
	MOVDQA  %xmm5, (%edi)
	mov	(%edi), %eax
	add	(%esi), %eax
	mov	%eax, (%esi)
	mov	4(%edi), %eax
	adc	4(%esi), %eax
	mov	%eax, 4(%esi)
	mov	8(%edi), %eax
	adc	8(%esi), %eax
	mov	%eax, 8(%esi)
	mov	12(%edi), %eax
	adc	12(%esi), %eax
	mov	%eax, 12(%esi)

	MOVDQA  %xmm4, (%edi)
	mov	(%edi), %eax
	add	%eax, (%esi)
	mov	4(%edi), %eax
	adc	%eax, 4(%esi)
	mov	8(%edi), %eax
	adc	%eax, 8(%esi)
	mov	12(%edi), %eax
	adc	%eax, 12(%esi)
	MOVDQA  (%esi), %xmm2
	movdqa	%xmm2, %xmm0
	call	printxmm0
m9:
	mov     %ebp, %eax
	sub	$4*2, %eax
	mov	%eax, %esp
	popl	%edi
	popl	%esi
	mov     %ebp, %esp
	pop     %ebp
	ret
//-------------------------------------------------------------

printxmm0:
	xor	%ecx, %ecx
	movdqa	%xmm0, %xmm7
m1:
	MOVDQA  %xmm7, (%esi)
	mov	(%esi), %ah
	PSRLDQ	$1, %xmm7
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
//	MOVDQA  %xmm0, (%esi)
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
//	MOVDQA  (%esi), %xmm0
	ret
