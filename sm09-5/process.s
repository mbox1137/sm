	.code32

	.data
inp_format:	.string "%d"
out_format:	.string " %d"
new_line:	.string "\n"

	.text
	.globl	process
	.type	process, @function

	.equ	N, -4*1
	.equ	num, -4*2

//void process(void);
process:
	push	%ebp
	mov	%esp, %ebp
	sub	$4*2, %esp	/* N, num */

	lea	N(%ebp), %eax
	push	%eax
	push	$inp_format
	call	scanf
	add	$4*2, %esp

	mov	N(%ebp), %ecx
m1:
	push	%ecx
	lea	num(%ebp), %eax
	push	%eax
	push	$inp_format
	call	scanf
	add	$4*2, %esp
	pop	%ecx
	cmp	$1, %eax
	jne	m9
	pushl	num(%ebp)
	loop	m1

	mov	N(%ebp), %ecx
m2:
	pop	%eax
	push	%ecx
	push	%eax
	push	$out_format
	call	printf
	add	$4*2, %esp
	pop	%ecx
	loop	m2

	push	$new_line
	call	printf
	add	$4*1, %esp
m9:
	mov	%ebp, %esp
	pop	%ebp
	ret
