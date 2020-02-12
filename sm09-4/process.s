//https://protocoder.ru/alg/datescrossing
//MAX(-MAX(a.min,b.min)+MIN (a.max,b.max),0)

	.code32

	.data
inp_format:	.string "%d%d%d%d"
out_format:	.string "%d"
new_line:	.string "\n"

	.text
	.globl	process
	.type	process, @function

	.equ	amin, -4*1
	.equ	amax, -4*2
	.equ	bmin, -4*3
	.equ	bmax, -4*4
	.equ	sumlen, -4*5

//void process(void);
process:
	push	%ebp
	mov	%esp, %ebp
	sub	$4*5, %esp
	xor	%eax, %eax
	mov	%eax, sumlen(%ebp)
m1:
	mov	%ebp, %eax
	add	$bmax, %eax
	push	%eax
	mov	%ebp, %eax
	add	$bmin, %eax
	push	%eax
	mov	%ebp, %eax
	add	$amax, %eax
	push	%eax
	mov	%ebp, %eax
	add	$amin, %eax
	push	%eax
	push	$inp_format
	call	scanf
	add	$4*5, %esp
	cmp	$4, %eax
	jne	m9
//---здесь должны быть вычисления---------------
	mov	amin(%ebp), %eax
	mov	amax(%ebp), %eax
	mov	bmin(%ebp), %eax
	mov	bmax(%ebp), %eax
	add	%eax, sumlen(%ebp)
//----------------------------------------------
	jmp	m1
m9:
	push	sumlen(%ebp)
	push	$out_format
	call	printf
	add	$4*2, %esp

	push	$new_line
	call	printf
	add	$4*1, %esp

	mov	%ebp, %esp
	pop	%ebp
	ret
