;https://forum.nasm.us/index.php?topic=1514.msg6228#msg6228
;
; Compiling this code for 32-bit use:
;    nasm -f elf file.asm
;    gcc -m32 -o file file.o
;
;~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.

SECTION .data
output_format: db "The number is "
input_format: db "%d" ; <~~ this is a bit of memory trickery, we reuse this part
end_of_format: db 0, 0 ; <~~ and change the first byte to a newline before output.

;~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.

SECTION .bss
input: resd 1 ; <~~ scanf handles conversion for us

;~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.

SECTION .text
extern printf
extern scanf
global main
main:
	nop
GetInput:
	;; Read input with scanf() function.
	push dword input
	push dword input_format
	call scanf
	add ESP, 8
Calculate:
	;; No need to calculate anything, scanf() handles input conversion.
Display:
	;; Display results using printf().
	mov byte [end_of_format], 10 ; <~~ add a newline for printf()
        push dword [input] ; <~~ here we pass the contents of our input variable.
        push output_format
        call printf
        add ESP, 8
        ret
