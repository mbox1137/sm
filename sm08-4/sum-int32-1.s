/*
 $ cat sum-int32-1.txt ;echo
1 2 3 4 5
 $ make
as -c --32 -o sum-int32-1.o sum-int32-1.s
gcc -m32 -no-pie -o sum-int32-1 sum-int32-1.o
 $ ./sum-int32-1.sh
./sum-int32-1 <sum-int32-1.txt
15
*/

		.code32

.data
input_format:	.string "%d"
output_format:	.string "%d\n"

.bss
num:	.space	4
sum:	.space	4

.text

.globl  main
.type   main, @function

main:
	xor	%eax, %eax
	movl	%eax, (sum)
m1:
	pushl	$num
	pushl	$input_format
	call	scanf
	add	$8, %esp
	cmp	$1, %eax
	mov	(sum), %eax
	jne	m2
	add	(num), %eax
	mov	%eax, (sum)
	jno	m1
	sar	$16, %eax
	sar	$16, %eax
	sar	$1, %eax
	cmc
	rcr	$1, %eax
m2:
	pushl	%eax
	pushl	$output_format
	call	printf
	popl	%eax
	popl	%ecx
	ret

        .size   main, . - main    /* размер функции main */
