	.code32

	.text
	.global process
	.type	process, @function

format_string:
	.string "%llu\n"

process:
	push	%ebp
	mov	%esp, %ebp

	push	%esi
	push	%edi

//A -> edi:esi
	mov	(A), %esi
	mov	(A+4), %edi 
// A*2 -> edi:esi
	shl	$1, %esi
	rcl	$1, %edi

//B -> edx:eax
	mov	(B), %eax
	mov	(B+4), %edx 
// B/2 -> edx:eax
	sar	$1, %edx
	rcr	$1, %eax

// edi:esi - edx:eax -> edi:esi
	sub	%eax, %esi
	sbb	%edx, %edi

	push	%edi
	push	%esi
	push	$format_string
	call	printf
	add	$12, %esp
m9:
	pop	%edi
	pop	%esi

	mov	%ebp, %esp
	pop	%ebp
	ret
