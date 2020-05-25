	.code32

	.text
	.globl	mystrcmp
	.type	mystrcmp, @function

	.equ	str1, 4*2
	.equ	str2, 4*3

//int mystrcmp(const char *str1, const char *str2);
mystrcmp:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%edi

	movl	str1(%ebp), %esi
	movl	str2(%ebp), %edi
	cld

loop1:
	lodsb
	subb	(%edi), %al
	jnz	calc		;
	cmpb	$0, (%edi)
	jz	calc		;
	incl	%edi
	jmp	loop1		;
calc:
	cmp	$0, %al
	je	return		;
	mov	$1, %al
	jns	return		;
	neg	%al
return:
	cbw
	cwde
	popl	%edi
	popl	%esi
	movl	%ebp, %esp
	popl	%ebp
	ret
