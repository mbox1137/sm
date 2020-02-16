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

loop1:
	cmpb	$0, (%esi)
	je	m2
	cmpb	$0, (%edi)
	je	m3

	movb	(%esi), %al
	cmpb	(%edi), %al
	jnz	calc
	incl	%esi
	incl	%edi
	jmp	loop1

m2:
	xorb	%al, %al
	cmpb	$0, (%edi)
	je	return
m4:
	movb	$-1, %al
	jmp	return

m3:
	movb	$1, %al
	jmp	return

calc:
	mov	(%esi), %al
	sub	(%edi), %al
//	cmp	$0, %al
	jl	m4
	jg	m3

return:
	cbw
	cwde
	popl	%edi
	popl	%esi
	movl	%ebp, %esp
	popl	%ebp
	ret
