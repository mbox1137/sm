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

	xor	%eax, %eax
	push	%eax
	xor	%edx, %edx
	cmp	$0, %ecx
	je	m4
	jl	m5
	inc	%eax
m1:
	cmp	%eax, %ecx
	jb	m2
	push	%eax
	mov	$10, %edx
	mul	%edx
	jmp	m1
m2:
	xor	%edx, %edx
	pop	%eax
	cmp	$0, %eax
	je	m5
m3:
	cmp	%eax, %ecx
	jb	m4
	sub	%eax, %ecx
	inc	%edx
	jmp	m3
m4:
	add	$'0', %edx
	push	%ecx
        push    (stout)
        push    %edx
        call    writechar
	add	$4*2, %esp
	pop	%ecx
	jmp	m2
m5:
        mov     %ebp, %esp
        pop     %ebp
        ret
