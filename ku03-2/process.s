//https://stackoverflow.com/questions/8776445/x86-imul-result-is-correct-why

	.text

	.equ	pa, 4 * 2
	.equ	b, pa + 4
	.equ	pc, b + 4

//int процесс(const signed char *a, int b, signed char *c);
	.globl	process
	.type	process, @function
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
	imull	b(%ebp)
	jo	er1
	movl	%eax, %ecx

	movl	$2, %eax
	imulb	(%esi)
	jo	er2

	cwde
	sub	%eax, %ecx
	jo	er3
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
