	.text
        .globl  forward_args
        .type   forward_args, @function

//forw(int v2, long long v3, float v4)
//proc(long long v2, float v4, unsigned v3)
forward_args:
	pushl   %ebp
        movl    %esp, %ebp
	pushl	%esi
	pushl	%edi

//передача параметров
        movl    -4(%ebp), %edi
        movl    -12(%ebp), %esi
        movss   -16(%ebp), %xmm0

//преобразовать типы и передать

	push	%ecx
        call	process
	addl	$4, %esp

return:
	popl	%edi
	popl	%esi
        movl	%ebp, %esp
	popl	%ebp
	ret
