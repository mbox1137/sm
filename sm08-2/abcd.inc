//Dirty %RAX !!!
	.macro	mover src, dst
	movl	\src, %eax
	CDQE
	movq	%rax, \dst
	.endm

	.macro	movre src, dst
	movq	\src, %rax
	movl	%eax, \dst
	.endm
