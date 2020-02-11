//https://protocoder.ru/alg/datescrossing
//MAX(-MAX(a.min,b.min)+MIN (a.max,b.max),0)

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
