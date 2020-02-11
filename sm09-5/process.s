	.code32

	.data
inp_format:	.string "%d"
out_format:	.string " %d"
new_line:	.string "\n"

	.text
	.globl	process
	.type	process, @function

	.equ	N, -4

//void process(void);
process:
	push	%ebp
	mov	%esp, %ebp
	sub	$4, %esp

	mov	%ebp, %eax
	add	$N, %eax
	push	%eax
	push	$inp_format
	call	scanf
	add	$4*2, %esp

	push	N(%ebp)
	push	$out_format
	call	printf
	add	$4*2, %esp

	push	$new_line
	call	printf
	add	$4*1, %esp

	mov	%ebp, %esp
	pop	%ebp
	ret
