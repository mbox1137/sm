	.code32

	.data
output_format:
	.string "%d %d %d\n"

	.text
        .global print_fib
	.type	print_fib, @function

print_fib:
        pushl   %ebp
        movl    %esp, %ebp

        movl    (A), %eax
        addl    (B), %eax
        movl    %eax, %ecx
        addl    (B), %ecx
        movl    %ecx, %edx
        addl    %eax, %edx

        pushl   %edx
        pushl   %ecx
        pushl   %eax
        pushl   $output_format
        call    printf
        addl    $4*4, %esp

        popl    %ebp
        xorl    %eax, %eax
        ret
