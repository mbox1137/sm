	.code32

	.text
	.globl	mystrcmp
	.type	mystrcmp, @function

	.equ	str1, 4*2
	.equ	str2, 4*3

	.equ	MAXLEN, 1000

//int mystrcmp(const char *str1, const char *str2);
mystrcmp:
	push	%ebp
	mov	%esp, %ebp
	push	%esi
	push	%edi

	cld	/* ++ */

	xor	%eax, %eax

	mov	$MAXLEN, %ecx
	mov	str1(%ebp), %edi
repnz	scasb
	sub	$MAXLEN, %ecx
	neg	%ecx

	mov	%ecx, %edx

	mov	$MAXLEN, %ecx
	mov	str2(%ebp), %edi
repnz	scasb
	sub	$MAXLEN, %ecx
	neg	%ecx

	cmp	%ecx, %edx
	jge	m2
	mov	%edx, %ecx
m2:

	mov	str1(%ebp), %esi
	mov	str2(%ebp), %edi
repz	cmpsb

	jz	m1
	mov	$1, %eax
	jg	m1
	neg	%eax
m1:
	pop	%edi
	pop	%esi
	mov	%ebp, %esp
	pop	%ebp
	ret
