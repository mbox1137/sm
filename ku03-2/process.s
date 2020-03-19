	.text
	.globl	process
	.type	process, @function


//int процесс(const signed char *a, int b, signed char *c);

	.equ	pa, 4 * 2
	.equ	b, pa + 4
	.equ	pc, b + 4

process:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%edi

	movl	pa(%ebp), %esi
	movl	pc(%ebp), %edi

//b * 3 - *a * 2
calc:
	movl	$3, %eax
	mull	b(%ebp)

	cmp	$0, %edx
	je	m1
	cmp	$-1, %edx
	je	m1
	jmp	er1
m1:
	movl	%eax, %ecx

	movl	$2, %eax
	mulb	(%esi)

	cmp	$0, %ah
	je	m2
	cmp	$-1, %ah
	je	m2
	jmp	er2

m2:
	cwde

	subl	%eax, %ecx
	cmp	$127, %ecx
	jg	er3
	cmp	$-128, %ecx
	jl	er3

	movb	%cl, (%edi)
	xorl	%eax, %eax
	jmp	return

er1:
	movl	$1, %eax
	jmp	return

er2:
	movl	$2, %eax
	jmp	return

er3:
	movl	$3, %eax
	jmp	return

return:
	movl	-4(%ebp), %esi
	movl	-8(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
