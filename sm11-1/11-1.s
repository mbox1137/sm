// семинар 10 февраля
#include <asm/unistd_32.h>

        .text
        .global _start
_start:
        subl    $1, %esp
cycle:
        movl    $__NR_read, %eax
        movl    $0, %ebx
        movl    %esp, %ecx
        movl    $1, %edx
        int     $0x80
        cmpl    $1, %eax
        jne     ending
        movzbl  (%esp), %esi
        cmpl    $'0', %esi
        jbe     next
        cmpl    $'9', %esi
        ja      next
        movl    $'0', (%esp)
next:
        movl    $__NR_write, %eax
        movl    $1, %ebx
        int     $0x80

        jmp     cycle
ending:
        addl    $2, %esp
        movl    $__NR_exit, %eax
        movl    $0, %ebx
        int     $0x80
