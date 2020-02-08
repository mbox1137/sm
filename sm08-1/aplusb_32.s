		.code32

.data
output_format:	.ascii "The sum is %d\n\0"
input_format:	.ascii "%d %d\0"

.bss
num1:
	.space	4
num2:
	.space	4
res_of_sum:
	.space	4

.text
.globl  main
.type   main, @function

main:
	pushl	%ebx

GetInput:
	pushl	$num2
	pushl	$num1
	pushl	$input_format
	call	scanf
	addl	$3*4, %esp

Calculate:
	movl	(num1), %eax
	addl	(num2), %eax
	movl	%eax, (res_of_sum)

Display:
	pushl	(res_of_sum)
	pushl	$output_format
        call	printf
	addl	$2*4, %esp

Return:
	pop	%ebx
        ret

        .size   main, . - main    /* размер функции main */
