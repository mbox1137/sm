	.code32

	.text
epsilon:
	.double	1.0e-8

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
m1:
	xorl	%eax, %eax
	cmp	$0, %esi
	je	m9

// if(fabs((node->key) - key)<1E-8)
	movsd	node_key(%esi), %xmm0
	subsd	key(%ebp), %xmm0
	xorpd	%xmm1, %xmm1
	subpd	%xmm0, %xmm1
	maxpd	%xmm1, %xmm0
	comisd	(epsilon), %xmm0

	ja	m2
	cmpl	$0, %edi
	je	m3
	movl	node_str(%esi), %eax
	movl	%eax, (%edi)
m3:
	xorl	%eax, %eax
	incl	%eax
	jmp	m9
m2:
	movl	node_right(%esi), %esi
	jmp	m1
m9:
	popl	%edi
	popl	%esi
	movl	%ebp, %esp
	popl	%ebp
	ret
