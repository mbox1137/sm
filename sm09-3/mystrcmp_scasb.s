//https://stackoverflow.com/questions/53934718/strcmp-in-intel-x86-with-cmpsb

	.code32

	.text
	.globl	mystrcmp
	.type	mystrcmp, @function

	.equ	str1, 4*2
	.equ	str2, 4*3

	.equ	MAXLEN, -1

//int mystrcmp(const char *str1, const char *str2);
mystrcmp:
	push	%ebp
	mov	%esp, %ebp
	push	%esi
	push	%edi

	cld	/* ++ */

	xor	%eax, %eax

//длина 1-й строки
	mov	$MAXLEN, %ecx
	mov	str1(%ebp), %edi
repnz	scasb
	sub	$MAXLEN, %ecx
	neg	%ecx

	mov	%ecx, %edx

//длина 2-й строки
	mov	$MAXLEN, %ecx
	mov	str2(%ebp), %edi
repnz	scasb
	sub	$MAXLEN, %ecx
	neg	%ecx

//наименьшая длина
	cmp	%ecx, %edx
	jge	m2
	mov	%edx, %ecx
m2:

//поиск несовпадения, но не больше длины наименьшей строки
	mov	str1(%ebp), %esi
	mov	str2(%ebp), %edi
repz	cmpsb

//https://c9x.me/x86/html/file_module_x86_id_288.html
	setnz	%al
	jge	m3
	neg	%eax
m3:

m1:
	pop	%edi
	pop	%esi
	mov	%ebp, %esp
	pop	%ebp
	ret
