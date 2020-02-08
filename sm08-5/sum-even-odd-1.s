/*
 $ make
as -c --32 -o sum-even-odd-1.o sum-even-odd-1.s
gcc -m32 -no-pie -o sum-even-odd-1 sum-even-odd-1.o
 $ ./sum-even-odd-1.sh
echo "1 2 3 4 5 6 7" |./sum-even-odd-1
12
16
*/

		.code32

.data
input_format:	.string "%d"
output_format:	.string "%d\n%d\n"
//output_format:	.string "%d %d\n"

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
	mov	%eax, %ebx
	and	$1, %ebx
	add	%eax, esum(,%ebx,4)
	jmp	m1
m2:
	pushl	(osum)
	pushl	(esum)
	pushl	$output_format
	call	printf
	add	$4*3, %esp
	ret

        .size   main, . - main    /* размер функции main */
