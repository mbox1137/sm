// код написан совместными усилиями на семинаре
	.code32

	.text
	.global process
	.type	process, @function

format_string:
	.string "%llu\n"

process:
	pushl	%ebp
	movl	%esp, %ebp

	pushl	%esi
	pushl	%edi

	//# right 32 bits
	movl	(A), %esi
	movl	(B), %edi

	//# left 32 bits, bigger address bigger bits
	movl	(A + 4), %eax
	movl	(B + 4), %edx

	//# A * 2
	shl	$1, %esi
	rcl	$1, %eax

	//# B / 2
	clc
	shr	$1, %edi
	rcr	$1, %edx

	sub	%edi, %esi
	sbbl	%edx, %eax

	pushl	%eax
	pushl	%esi
	pushl	$format_string
	//# or use: lea   format_string   %ecx
	call	printf

	//# 12 bytes were reserved and we
	//# need to move them back

	addl	$12, %esp
	//# addl	$4, %esp
	/*popl	%eax
	popl	%edx*/

	//# pop in reverse order
	popl	%edi
	popl	%esi

	movl	%ebp, %esp
	popl	%ebp
	ret
