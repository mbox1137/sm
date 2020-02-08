		.code64

	.include "abcd.inc"

.text

.globl  process
.type   process, @function
//RDI*RSI + RDX*RCX
process:
	push	%rbx
	movq	%rdx, %rax
	mulq	%rcx
	movq	%rax, %rbx
	movq	%rdi, %rax
	mulq	%rsi
	addq	%rbx, %rax
	pop	%rbx
        ret

        .size   process, . - process    /*размер функции*/
