//https://neerc.ifmo.ru/wiki/index.php?title=%D0%9E%D1%81%D0%BD%D0%BE%D0%B2%D0%BD%D1%8B%D0%B5_%D0%BE%D0%BF%D1%80%D0%B5%D0%B4%D0%B5%D0%BB%D0%B5%D0%BD%D0%B8%D1%8F_%D1%82%D0%B5%D0%BE%D1%80%D0%B8%D0%B8_%D0%B3%D1%80%D0%B0%D1%84%D0%BE%D0%B2
//Дерево (англ. tree) — связный ациклический граф.

	.code32

	.text
epsilon:
	.double	1.0e-8
two:
	.double	2.0

	.globl	tree_find
	.type	tree_find, @function

	.equ	root, 4*2	/* old ebp, ret address	*/
	.equ	key, root+4	/* root + sizeof(*root)	*/
	.equ	pstr, key+8	/* key + sizeof(key)	*/
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
// int tree_find(struct Node *root, double key, char **pstr);
tree_find:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%edi

	movl	root(%ebp), %esi
	movl	pstr(%ebp), %edi
	movsd	key(%ebp), %xmm2

	call	scan_tree
	xor	%eax, %eax
	jmp	m9

scan_tree:
	cmpl	$0, %esi
	jne	m2
m1:
	ret
m2:
	push	%esi
	movl	node_left(%esi), %esi
	call	scan_tree
	pop	%esi

	push	%esi
	movl	node_right(%esi), %esi
	call	scan_tree
	pop	%esi

// xmm2 == key(%ebp)
// xmm3 == (epsilon)
// xmm4 == 2.0 (two)
// xmm0 == node->key -> node->key-key -> (node->key-key)/(node->key+key)
// xmm1 == node->key -> node->key+key
	movsd	key(%ebp), %xmm2
	movsd	(epsilon), %xmm3
	movsd	(two), %xmm4
// fabs(2.0 * (node->key - key) / (node->key + key)) < 1E-8
	movsd	node_key(%esi), %xmm0
	movsd	%xmm0, %xmm1
	subsd	%xmm2, %xmm0
	addsd	%xmm2, %xmm1
	divsd	%xmm1, %xmm0
	mulsd	%xmm4, %xmm0
	xorpd	%xmm1, %xmm1
	subpd	%xmm0, %xmm1
	maxpd	%xmm1, %xmm0
	comisd	%xmm3, %xmm0
	jb	m3
// if(fabs((node->key) - key)<1E-8)
	movsd	node_key(%esi), %xmm0
	subsd	%xmm2, %xmm0
	xorpd	%xmm1, %xmm1
	subpd	%xmm0, %xmm1
	maxpd	%xmm1, %xmm0
	comisd	%xmm3, %xmm0
	jb	m3
	jmp	m1
m3:
	mov	$1, %eax
	cmp	$0, %edi
	je	m4
	mov	node_str(%esi), %edx
	mov	%edx, (%edi)
m4:
m9:
	mov	-4(%ebp), %esi
	mov	-8(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret

	.size   tree_find, . - tree_find
