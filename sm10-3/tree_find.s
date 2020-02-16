//https://ru.bmstu.wiki/SSE2_(Streaming_SIMD_Extensions_2)

	.code32

	.data

	.text
	.globl	tree_find
	.type	tree_find, @function

	.equ	root, 4*2	/* old ebp, ret address		*/
	.equ	key, root+4	/* root + sizeof(*root)	*/
	.equ	pstr, key+8	/* key + sizeof(key)		*/
/*
	double	key;
	struct	Node *left;
	struct	Node *right;
	char	*str;
*/
	.equ	node_key, 0
	.equ	node_left, node_key + 8
	.equ	node_right, node_left + 4
	.equ	node_str, node_right + 4
//int tree_find(struct Node *root, double key, char **pstr);
tree_find:
	push	%ebp
	mov	%esp, %ebp
	push	%esi
	push	%edi
	mov	root(%ebp), %esi
	mov	pstr(%ebp), %edi
	movsd	key(%ebp), %xmm7
m1:
	xor	%eax, %eax
	test	$-1, %esi
	je	m9
	movsd	node_key(%esi), %xmm0
/*
if(fabs((node->key) - key)<1E-8)
	jg	m2
*/
	jmp	m2
	test	$-1, %edi
	je	m3
	mov	node_str(%esi), %eax
	mov	%eax, (%edi)
m3:
	xor	%eax, %eax
	inc	%eax
	jmp	m9
m2:
/*
	sub	$8*1, %esp

	movsd	X(%ebp), %xmm0

	movsd	%xmm0, %xmm1
	mulsd	%xmm1, %xmm0

	movsd	Y(%ebp), %xmm2
	movsd	%xmm2, %xmm3
	mulsd	%xmm3, %xmm2

	addsd	%xmm0, %xmm2
	sqrtsd	%xmm2, %xmm0

	movsd	%xmm0, TMP(%ebp)
	fldl	TMP(%ebp)
*/
m9:
	pop	%edi
	pop	%esi
	mov	%ebp, %esp
	pop	%ebp
	ret
