//Dirty %RAX !!!
	.macro	mover src, dst
	movl	\src, %eax
	CDQE
	movq	%rax, \dst
	.endm
