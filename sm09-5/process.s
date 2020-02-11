	.code32

	.data
inp_format:	.string "%d"
out_format:	.string " %d"
new_line:	.string "\n"

	.text
	.globl	process
	.type	process, @function

	.equ	N, -4
	.equ	ncx, -8

//void process(void);
process:
	push	%ebp
	mov	%esp, %ebp
	sub	$4*2, %esp	/* N, ncx */

	mov	%ebp, %eax
	add	$N, %eax
	push	%eax
	push	$inp_format
	call	scanf
	add	$4*2, %esp

	mov	N(%ebp), %ecx
m1:
	sub	$4, %esp
	mov	%esp, (%esp)
	push	$inp_format
	mov	%ecx, ncx(%ebp)
	call	scanf
	mov	ncx(%ebp), %ecx
	add	$4*1, %esp
	loop	m1


	mov	N(%ebp), %ecx
m2:
	push	$out_format
	mov	%ecx, ncx(%ebp)
	call	printf
	mov	ncx(%ebp), %ecx
	add	$4*2, %esp
	loop	m2

	push	$new_line
	call	printf
	add	$4*1, %esp

	mov	%ebp, %esp
	pop	%ebp
	ret
