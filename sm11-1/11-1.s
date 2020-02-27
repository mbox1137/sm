// семинар 10 февраля
#include <asm/unistd_32.h>

        .text
        .global _start

_start:
        subl    $4, %esp
cycle:
        movl    $3, %eax
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
        movl    $4, %eax
        movl    $1, %ebx
        int     $0x80

        jmp     cycle
ending:
        addl    $4, %esp
        movl    $1, %eax
        movl    $0, %ebx
        int     $0x80
