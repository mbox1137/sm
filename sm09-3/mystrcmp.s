	.code32

	.text
	.globl	mystrcmp
	.type	mystrcmp, @function

	.equ	str1, 4*2
	.equ	str2, 4*3

//int mystrcmp(const char *str1, const char *str2);
mystrcmp:
	push	%ebp
	mov	%esp, %ebp
	push	%esi
	push	%edi

	mov	str1(%ebp), %esi
	mov	str2(%ebp), %edi
	cld	/* ++ */
m1:
	lodsb	/* al=(%esi++) */
	sub	(%edi), %al
	jne	m2
	scasb	/* al == (%edi++) ???; al==0 */
	jne	m1
m2:
	cbw	/* al -> ax */
	cwde	/* ax -> eax */
m9:
	pop	%edi
	pop	%esi
	mov	%ebp, %esp
	pop	%ebp
	ret
