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

	xorl	%eax, %eax
	cmpl	$0, %esi
	je	m9

m5:
	movl	node_left(%esi), %eax
	cmpl	$0, %eax
	je	m4

	movl	node_left(%esi), %esi
	jmp	m5
m4:
	movsd	key(%ebp), %xmm2

m1:
	xorl	%eax, %eax
	cmpl	$0, %esi
	je	m9
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
	jb	m6
// if(fabs((node->key) - key)<1E-8)
	movsd	node_key(%esi), %xmm0
	subsd	%xmm2, %xmm0
	xorpd	%xmm1, %xmm1
	subpd	%xmm0, %xmm1
	maxpd	%xmm1, %xmm0
	comisd	%xmm3, %xmm0
	jb	m6

	movl	node_right(%esi), %esi
	jmp	m1
m6:
	cmpl	$0, %edi
	je	m3
	movl	node_str(%esi), %eax
	movl	%eax, (%edi)
m3:
	xorl	%eax, %eax
	incl	%eax
m9:
	popl	%edi
	popl	%esi
	movl	%ebp, %esp
	popl	%ebp
	ret
