	.text
        .globl  forward$args
        .type   forward$args, @function
        .globl  process
        .type   process, @function

//forw(int v2, long long v3, float v4)
//proc(long long v2, float v4, unsigned v3)

	.equ    v2, 4*2
	.equ    v3, v2+4
	.equ    v4, v3+8

forward$args:
	pushl   %ebp
        movl    %esp, %ebp
	pushl	%esi
	pushl	%edi

//передача параметров

//преобразовать типы и передать
//forw(int v2, long long v3, float v4)
//proc(void *p, long long v2, float v4, unsigned v3)
        movl    v3(%ebp), %esi
        movl    v3+4(%ebp), %edi
	push	%esi

        movss   v4(%ebp), %xmm0
	sub	$4, %esp
	movss	%xmm0, (%esp)

        movl    v2(%ebp), %eax
	cdq
	push	%edx
	push	%eax

	push	%ecx

        call	process
	neg	%eax
	addl	$4+4+4+4+4, %esp
return:
	mov	-4(%ebp), %esi
	mov	-8(%ebp), %edi
        movl	%ebp, %esp
	popl	%ebp
	ret
