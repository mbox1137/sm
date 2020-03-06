	.text
        .global writeu32
	.type   writeu32, @function
        .global writechar
	.type   writechar, @function
        .global stout

//:"c"(n)
writeu32:
        push    %ebp
        mov     %esp, %ebp
        push    %ebx
        push    %esi
        push    %edi

print:
        push    (stout)
        push    %ecx
        call    writechar
	add	$4*2, %esp
fin:
        pop     %edi
        pop     %esi
        pop     %ebx
        mov     %ebp, %esp
        pop     %ebp
        ret
