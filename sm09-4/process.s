//https://stackoverflow.com/questions/53934718/strcmp-in-intel-x86-with-cmpsb

	.code32

	.text
	.globl	process
	.type	process, @function

//void process(void);
process:
	push	%ebp
	mov	%esp, %ebp
	push	%esi
	push	%edi

	pop	%edi
	pop	%esi
	mov	%ebp, %esp
	pop	%ebp
	ret
