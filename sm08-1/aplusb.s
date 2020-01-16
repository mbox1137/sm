/*
https://ru.wikibooks.org/wiki/%D0%90%D1%81%D1%81%D0%B5%D0%BC%D0%B1%D0%BB%D0%B5%D1%80_%D0%B2_Linux_%D0%B4%D0%BB%D1%8F_%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D0%B8%D1%81%D1%82%D0%BE%D0%B2_C
https://forum.nasm.us/index.php?topic=1514.msg6228#msg6228
$ gcc -m32 -c -o aplusb.o aplusb.s
$ gcc -m32 -o aplusb aplusb.o
$ echo 123|./aplusb
The number+1 is 124
*/

		.code32

.data
output_format:	.ascii "The number+1 is "
input_format:	.ascii "%d"
end_of_format:	.ascii "\0\0"
//dprintf:	.long	$printf

.bss
num1:
	.space	4

.text
.globl  main
.type   main, @function

main:
	nop

GetInput:
	pushl	$num1
	pushl	$input_format
	call	scanf
	addl	$8, %ESP

Calculate:

Display:
	movb	$10, (end_of_format)
	movl	(num1), %eax
	incl	%eax
        pushl	%eax
        pushl	$output_format
        call	printf
//	call	(dprintf)
	addl	$8, %ESP
        ret

        .size   main, . - main    /* размер функции main */
