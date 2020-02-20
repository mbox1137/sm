	.code32

	.text
	.global A, B
	.global process
	.type	process, @function

f_string:
	.string "%lld "
format_string:
	.string "%llx\n"

process:
	push	%ebp
	mov	%esp, %ebp

	push	%esi
	push	%edi

//A -> edi:esi
	mov	(A), %esi
	mov	(A+4), %edi 
/*
	push	%edi
	push	%esi
	push	$format_string
	call	printf
	add	$4, %esp
	pop	%esi
	pop	%edi
*/
// A*2 -> edi:esi
	shl	%esi
	rcl	%edi
/*
	push	%edi
	push	%esi
	push	$format_string
	call	printf
	add	$4, %esp
	pop	%esi
	pop	%edi
*/
//B -> edx:eax
	mov	(B), %eax
	mov	(B+4), %edx 
/*
	push	%edi
	push	%esi
	push	%edx
	push	%eax
	push	$format_string
	call	printf
	add	$4, %esp
	pop	%eax
	pop	%edx
	pop	%esi
	pop	%edi
*/
// B/2 -> edx:eax
	shr	%edx
	rcr	%eax
/*
	push	%edi
	push	%esi
	push	%edx
	push	%eax
	push	$format_string
	call	printf
	add	$4, %esp
	pop	%eax
	pop	%edx
	pop	%esi
	pop	%edi
*/
// edi:esi - edx:eax -> edi:esi
	sub	%eax, %esi
	sbb	%edx, %edi

//Печать десятичная
	push	%edi
	push	%esi
	push	$f_string
	call	printf
	add	$4, %esp
	pop	%esi
	pop	%edi

//Печать шестнадцатиричная
	push	%edi
	push	%esi
	push	$format_string
	call	printf
	add	$4, %esp
	pop	%esi
	pop	%edi
m9:
	pop	%edi
	pop	%esi

	mov	%ebp, %esp
	pop	%ebp
	ret
