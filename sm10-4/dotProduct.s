//https://gamedev.ru/code/articles/?id=4238&page=5
//https://books.google.ru/books?id=KM0aV15kPi4C&pg=PA605&lpg=PA605&dq=assembler+xmm0+%D0%B2%D0%BE%D0%B7%D0%B2%D1%80%D0%B0%D1%82+%D0%B7%D0%BD%D0%B0%D1%87%D0%B5%D0%BD%D0%B8%D1%8F+%D0%A1&source=bl&ots=tVTZ4_dLam&sig=ACfU3U2v9kP38TRTL0WrqRdIb3bzFgAjeg&hl=ru&sa=X&ved=2ahUKEwjprbSZ69_nAhWNpYsKHUy7DewQ6AEwAHoECAoQAQ#v=onepage&q=assembler%20xmm0%20%D0%B2%D0%BE%D0%B7%D0%B2%D1%80%D0%B0%D1%82%20%D0%B7%D0%BD%D0%B0%D1%87%D0%B5%D0%BD%D0%B8%D1%8F%20%D0%A1&f=false
//стр. 615

	.code32
/*
	.data
epsilon:	.float 1.0E-8
*/
	.text
	.globl  dotProduct
	.type   dotProduct, @function
	.globl  dp
	.type   dp, @function

	.equ    N, 4*2
	.equ    X, N+4
	.equ    Y, X+4
	.equ    TMP, -4*1

//float dotProduct(int n, float *x, float *y);
dp:
	push    %ebp
	mov     %esp, %ebp
	sub     $4*1, %esp	/* tmp */
	push	%esi
	push	%edi

	mov	X(%ebp), %esi
	mov	Y(%ebp), %edi

	movups	(%esi), %xmm0
	movups	(%edi), %xmm1
	mulps	%xmm1, %xmm0
//01 00 11 10
	shufps	$0x4E, %xmm0, %xmm1
	addps	%xmm1, %xmm0
//10 00 01 01
	shufps	$0x85, %xmm0, %xmm1
	addps	%xmm1, %xmm0

//00 01 10 11 : xmm0.{3,2,1,0} == xmm0.{0,1,2,3}
	shufps	$0x1B, %xmm0, %xmm0

//single(%xmm0)=%xmm0.3 !!!
	movss   %xmm0, TMP(%ebp)
	fld	TMP(%ebp)
m9:
	pop	%edi
	pop	%esi
	mov     %ebp, %esp
	pop     %ebp
	ret

dotProduct:
	push    %ebp
	mov     %esp, %ebp

	push	Y(%ebp)
	push	X(%ebp)
	push	N(%ebp)
	call	dp

	mov     %ebp, %esp
	pop     %ebp
	ret
