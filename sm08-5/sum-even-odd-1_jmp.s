/*
*/

		.code32

.data
input_format:	.string "%d"
output_format:	.string "%d\n%d\n"

.bss
num:	.space	4
esum:	.space	4
osum:	.space	4

.text

.globl  main
.type   main, @function

main:
	xor	%eax, %eax
	mov	%eax, (esum)
	mov	%eax, (osum)
m1:
	pushl	$num
	pushl	$input_format
	call	scanf
	add	$4*2, %esp
	cmp	$1, %eax
	jne	m2
	mov	(num), %eax
	test	$1, %eax
	jnz	m3
	add	%eax, (esum)
	jmp	m4
m3:
	add	%eax, (osum)
m4:
	jmp	m1
m2:
	pushl	(osum)
	pushl	(esum)
	pushl	$output_format
	call	printf
	add	$4*3, %esp
	ret

        .size   main, . - main    /* размер функции main */
