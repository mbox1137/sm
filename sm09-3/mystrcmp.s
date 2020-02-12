	.code32

	.text
	.globl	mystrcmp
	.type	mystrcmp, @function

	.equ	str1, 4*2
	.equ	str2, 4*3

	.equ	MAXLEN, -1

//int mystrcmp(const char *str1, const char *str2);
mystrcmp:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%edi

	movl	str1(%ebp), %esi
	movl	str2(%ebp), %edi

loop1:
	cmpb	$0, (%esi)
	je	m2
	cmpb	$0, (%edi)
	je	m3

	movb	(%esi), %al
	cmp	(%edi), %al
	jnz	calc
	incl	%esi
	incl	%edi
	jmp	loop1

m2:
	xorl	%eax, %eax
	cmpb	$0, (%edi)
	je	return
	jmp	calc

m3:
	movb	$1, %al
	jmp	return

calc:
	mov	(%esi), %al
	sub	(%edi), %al

return:
	cbw
	cwde
	popl	%edi
	popl	%esi
	movl	%ebp, %esp
	popl	%ebp
	ret
