	.file	"main.c"
# GNU C11 (Ubuntu 7.5.0-3ubuntu1~18.04) version 7.5.0 (x86_64-linux-gnu)
#	compiled by GNU C version 7.5.0, GMP version 6.1.2, MPFR version 4.0.1, MPC version 1.1.0, isl version isl-0.19-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -imultilib 32 -imultiarch i386-linux-gnu main.c -m32
# -mtune=generic -march=i686 -auxbase-strip main.s -g -Wunused-variable
# -Werror=return-type -Werror=dangling-else -fverbose-asm
# -fstack-protector-strong -Wformat -Wformat-security
# options enabled:  -fPIC -fPIE -faggressive-loop-optimizations
# -fasynchronous-unwind-tables -fauto-inc-dec -fchkp-check-incomplete-type
# -fchkp-check-read -fchkp-check-write -fchkp-instrument-calls
# -fchkp-narrow-bounds -fchkp-optimize -fchkp-store-bounds
# -fchkp-use-static-bounds -fchkp-use-static-const-bounds
# -fchkp-use-wrappers -fcommon -fdelete-null-pointer-checks
# -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-types
# -ffp-int-builtin-inexact -ffunction-cse -fgcse-lm -fgnu-runtime
# -fgnu-unique -fident -finline-atomics -fira-hoist-pressure
# -fira-share-save-slots -fira-share-spill-slots -fivopts
# -fkeep-static-consts -fleading-underscore -flifetime-dse
# -flto-odr-type-merging -fmath-errno -fmerge-debug-strings
# -fpcc-struct-return -fpeephole -fplt -fprefetch-loop-arrays
# -fsched-critical-path-heuristic -fsched-dep-count-heuristic
# -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
# -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
# -fsched-stalled-insns-dep -fschedule-fusion -fsemantic-interposition
# -fshow-column -fshrink-wrap-separate -fsigned-zeros
# -fsplit-ivs-in-unroller -fssa-backprop -fstack-protector-strong
# -fstdarg-opt -fstrict-volatile-bitfields -fsync-libcalls -ftrapping-math
# -ftree-cselim -ftree-forwprop -ftree-loop-if-convert -ftree-loop-im
# -ftree-loop-ivcanon -ftree-loop-optimize -ftree-parallelize-loops=
# -ftree-phiprop -ftree-reassoc -ftree-scev-cprop -funit-at-a-time
# -funwind-tables -fverbose-asm -fzero-initialized-in-bss -m32 -m80387
# -m96bit-long-double -malign-stringops -mavx256-split-unaligned-load
# -mavx256-split-unaligned-store -mfancy-math-387 -mfp-ret-in-387 -mglibc
# -mieee-fp -mlong-double-80 -mno-red-zone -mno-sse4 -mpush-args -msahf
# -mstv -mtls-direct-seg-refs -mvzeroupper

	.text
.Ltext0:
	.globl	counter
	.bss
	.align 4
	.type	counter, @object
	.size	counter, 4
counter:
	.zero	4
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	func
	.type	func, @function
func:
.LFB5:
	.file 1 "main.c"
	.loc 1 9 0
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
	pushl	%ebx	#
	subl	$4, %esp	#,
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx	#
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx	# tmp87,
# main.c:12:     if (counter == 4)
	.loc 1 12 0
	movl	counter@GOTOFF(%ebx), %eax	# counter, counter.0_1
	cmpl	$4, %eax	#, counter.0_1
	jne	.L2	#,
# main.c:13:         _exit(EXIT_SUCCESS);
	.loc 1 13 0
	subl	$12, %esp	#,
	pushl	$0	#
	call	_exit@PLT	#
.L2:
# main.c:15:     printf("%d\n", counter);
	.loc 1 15 0
	movl	counter@GOTOFF(%ebx), %eax	# counter, counter.1_2
	subl	$8, %esp	#,
	pushl	%eax	# counter.1_2
	leal	.LC0@GOTOFF(%ebx), %eax	#, tmp93
	pushl	%eax	# tmp93
	call	printf@PLT	#
	addl	$16, %esp	#,
# main.c:16:     counter++;
	.loc 1 16 0
	movl	counter@GOTOFF(%ebx), %eax	# counter, counter.2_3
	addl	$1, %eax	#, _4
	movl	%eax, counter@GOTOFF(%ebx)	# _4, counter
# main.c:18:     fflush(stdout);
	.loc 1 18 0
	movl	stdout@GOT(%ebx), %eax	#, tmp94
	movl	(%eax), %eax	# stdout, stdout.3_5
	subl	$12, %esp	#,
	pushl	%eax	# stdout.3_5
	call	fflush@PLT	#
	addl	$16, %esp	#,
# main.c:19: }
	.loc 1 19 0
	nop
	movl	-4(%ebp), %ebx	#,
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE5:
	.size	func, .-func
	.globl	main
	.type	main, @function
main:
.LFB6:
	.loc 1 23 0
	.cfi_startproc
	leal	4(%esp), %ecx	#,
	.cfi_def_cfa 1, 0
	andl	$-16, %esp	#,
	pushl	-4(%ecx)	#
	pushl	%ebp	#
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp	#,
	pushl	%edi	#
	pushl	%ebx	#
	pushl	%ecx	#
	.cfi_escape 0xf,0x3,0x75,0x74,0x6
	.cfi_escape 0x10,0x7,0x2,0x75,0x7c
	.cfi_escape 0x10,0x3,0x2,0x75,0x78
	subl	$300, %esp	#,
	call	__x86.get_pc_thunk.bx	#
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx	# tmp87,
	movl	%ecx, %eax	#, tmp103
	movl	4(%eax), %eax	# argv, tmp91
	movl	%eax, -300(%ebp)	# tmp91, argv
# main.c:23: {
	.loc 1 23 0
	movl	%gs:20, %eax	#, tmp104
	movl	%eax, -28(%ebp)	# tmp104, D.3350
	xorl	%eax, %eax	# tmp104
# main.c:27:     struct sigaction sa = {}; // инициализируем нулями
	.loc 1 27 0
	leal	-168(%ebp), %edx	#, tmp92
	movl	$0, %eax	#, tmp93
	movl	$35, %ecx	#, tmp94
	movl	%edx, %edi	# tmp92, tmp92
	rep stosl
# main.c:28:     sa.sa_flags = SA_RESTART; // restartable system calls
	.loc 1 28 0
	movl	$268435456, -36(%ebp)	#, sa.sa_flags
# main.c:29:     sa.sa_handler = func;     // обработчик сигнала
	.loc 1 29 0
	leal	func@GOTOFF(%ebx), %eax	#, tmp95
	movl	%eax, -168(%ebp)	# tmp95, sa.__sigaction_handler.sa_handler
# main.c:30:     sigaction(SIGINT, &sa, 0);
	.loc 1 30 0
	subl	$4, %esp	#,
	pushl	$0	#
	leal	-168(%ebp), %eax	#, tmp96
	pushl	%eax	# tmp96
	pushl	$2	#
	call	sigaction@PLT	#
	addl	$16, %esp	#,
# main.c:33:     sigemptyset(&mask);
	.loc 1 33 0
	subl	$12, %esp	#,
	leal	-296(%ebp), %eax	#, tmp97
	pushl	%eax	# tmp97
	call	sigemptyset@PLT	#
	addl	$16, %esp	#,
# main.c:34:     sigaddset(&mask, SIGINT);
	.loc 1 34 0
	subl	$8, %esp	#,
	pushl	$2	#
	leal	-296(%ebp), %eax	#, tmp98
	pushl	%eax	# tmp98
	call	sigaddset@PLT	#
	addl	$16, %esp	#,
# main.c:36:     sigprocmask(SIG_BLOCK, &mask, 0);
	.loc 1 36 0
	subl	$4, %esp	#,
	pushl	$0	#
	leal	-296(%ebp), %eax	#, tmp99
	pushl	%eax	# tmp99
	pushl	$0	#
	call	sigprocmask@PLT	#
	addl	$16, %esp	#,
# main.c:37:     printf("%d\n", getpid());
	.loc 1 37 0
	call	getpid@PLT	#
	subl	$8, %esp	#,
	pushl	%eax	# _1
	leal	.LC0@GOTOFF(%ebx), %eax	#, tmp100
	pushl	%eax	# tmp100
	call	printf@PLT	#
	addl	$16, %esp	#,
# main.c:38:     fflush(stdout);
	.loc 1 38 0
	movl	stdout@GOT(%ebx), %eax	#, tmp101
	movl	(%eax), %eax	# stdout, stdout.4_2
	subl	$12, %esp	#,
	pushl	%eax	# stdout.4_2
	call	fflush@PLT	#
	addl	$16, %esp	#,
# main.c:39:     sigprocmask(SIG_UNBLOCK, &mask, NULL);
	.loc 1 39 0
	subl	$4, %esp	#,
	pushl	$0	#
	leal	-296(%ebp), %eax	#, tmp102
	pushl	%eax	# tmp102
	pushl	$1	#
	call	sigprocmask@PLT	#
	addl	$16, %esp	#,
.L4:
# main.c:42:         pause();
	.loc 1 42 0 discriminator 1
	call	pause@PLT	#
	jmp	.L4	#
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB7:
	.cfi_startproc
	movl	(%esp), %ebx	#,
	ret
	.cfi_endproc
.LFE7:
	.text
.Letext0:
	.file 2 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h"
	.file 3 "/usr/include/bits/types.h"
	.file 4 "/usr/include/bits/libio.h"
	.file 5 "/usr/include/stdio.h"
	.file 6 "/usr/include/bits/sys_errlist.h"
	.file 7 "/usr/include/bits/types/__sigset_t.h"
	.file 8 "/usr/include/bits/types/sigset_t.h"
	.file 9 "/usr/include/bits/types/__sigval_t.h"
	.file 10 "/usr/include/bits/types/siginfo_t.h"
	.file 11 "/usr/include/signal.h"
	.file 12 "/usr/include/bits/sigaction.h"
	.file 13 "/usr/include/unistd.h"
	.file 14 "/usr/include/bits/getopt_core.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x767
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF118
	.byte	0xc
	.long	.LASF119
	.long	.LASF120
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF6
	.byte	0x2
	.byte	0xd8
	.long	0x30
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF0
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF2
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x5
	.long	0x5a
	.uleb128 0x2
	.long	.LASF7
	.byte	0x3
	.byte	0x29
	.long	0x30
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF8
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF9
	.uleb128 0x2
	.long	.LASF10
	.byte	0x3
	.byte	0x37
	.long	0x71
	.uleb128 0x2
	.long	.LASF11
	.byte	0x3
	.byte	0x86
	.long	0x30
	.uleb128 0x2
	.long	.LASF12
	.byte	0x3
	.byte	0x8c
	.long	0xa0
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.long	.LASF13
	.uleb128 0x2
	.long	.LASF14
	.byte	0x3
	.byte	0x8d
	.long	0x7f
	.uleb128 0x2
	.long	.LASF15
	.byte	0x3
	.byte	0x8e
	.long	0x5a
	.uleb128 0x2
	.long	.LASF16
	.byte	0x3
	.byte	0x90
	.long	0xa0
	.uleb128 0x6
	.byte	0x4
	.uleb128 0x7
	.byte	0x4
	.long	0xd0
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF17
	.uleb128 0x8
	.long	0xd0
	.uleb128 0x9
	.long	.LASF47
	.byte	0x94
	.byte	0x4
	.byte	0xf5
	.long	0x25c
	.uleb128 0xa
	.long	.LASF18
	.byte	0x4
	.byte	0xf6
	.long	0x5a
	.byte	0
	.uleb128 0xa
	.long	.LASF19
	.byte	0x4
	.byte	0xfb
	.long	0xca
	.byte	0x4
	.uleb128 0xa
	.long	.LASF20
	.byte	0x4
	.byte	0xfc
	.long	0xca
	.byte	0x8
	.uleb128 0xa
	.long	.LASF21
	.byte	0x4
	.byte	0xfd
	.long	0xca
	.byte	0xc
	.uleb128 0xa
	.long	.LASF22
	.byte	0x4
	.byte	0xfe
	.long	0xca
	.byte	0x10
	.uleb128 0xa
	.long	.LASF23
	.byte	0x4
	.byte	0xff
	.long	0xca
	.byte	0x14
	.uleb128 0xb
	.long	.LASF24
	.byte	0x4
	.value	0x100
	.long	0xca
	.byte	0x18
	.uleb128 0xb
	.long	.LASF25
	.byte	0x4
	.value	0x101
	.long	0xca
	.byte	0x1c
	.uleb128 0xb
	.long	.LASF26
	.byte	0x4
	.value	0x102
	.long	0xca
	.byte	0x20
	.uleb128 0xb
	.long	.LASF27
	.byte	0x4
	.value	0x104
	.long	0xca
	.byte	0x24
	.uleb128 0xb
	.long	.LASF28
	.byte	0x4
	.value	0x105
	.long	0xca
	.byte	0x28
	.uleb128 0xb
	.long	.LASF29
	.byte	0x4
	.value	0x106
	.long	0xca
	.byte	0x2c
	.uleb128 0xb
	.long	.LASF30
	.byte	0x4
	.value	0x108
	.long	0x294
	.byte	0x30
	.uleb128 0xb
	.long	.LASF31
	.byte	0x4
	.value	0x10a
	.long	0x29a
	.byte	0x34
	.uleb128 0xb
	.long	.LASF32
	.byte	0x4
	.value	0x10c
	.long	0x5a
	.byte	0x38
	.uleb128 0xb
	.long	.LASF33
	.byte	0x4
	.value	0x110
	.long	0x5a
	.byte	0x3c
	.uleb128 0xb
	.long	.LASF34
	.byte	0x4
	.value	0x112
	.long	0x95
	.byte	0x40
	.uleb128 0xb
	.long	.LASF35
	.byte	0x4
	.value	0x116
	.long	0x3e
	.byte	0x44
	.uleb128 0xb
	.long	.LASF36
	.byte	0x4
	.value	0x117
	.long	0x4c
	.byte	0x46
	.uleb128 0xb
	.long	.LASF37
	.byte	0x4
	.value	0x118
	.long	0x2a0
	.byte	0x47
	.uleb128 0xb
	.long	.LASF38
	.byte	0x4
	.value	0x11c
	.long	0x2b0
	.byte	0x48
	.uleb128 0xb
	.long	.LASF39
	.byte	0x4
	.value	0x125
	.long	0xa7
	.byte	0x4c
	.uleb128 0xb
	.long	.LASF40
	.byte	0x4
	.value	0x12d
	.long	0xc8
	.byte	0x54
	.uleb128 0xb
	.long	.LASF41
	.byte	0x4
	.value	0x12e
	.long	0xc8
	.byte	0x58
	.uleb128 0xb
	.long	.LASF42
	.byte	0x4
	.value	0x12f
	.long	0xc8
	.byte	0x5c
	.uleb128 0xb
	.long	.LASF43
	.byte	0x4
	.value	0x130
	.long	0xc8
	.byte	0x60
	.uleb128 0xb
	.long	.LASF44
	.byte	0x4
	.value	0x132
	.long	0x25
	.byte	0x64
	.uleb128 0xb
	.long	.LASF45
	.byte	0x4
	.value	0x133
	.long	0x5a
	.byte	0x68
	.uleb128 0xb
	.long	.LASF46
	.byte	0x4
	.value	0x135
	.long	0x2b6
	.byte	0x6c
	.byte	0
	.uleb128 0xc
	.long	.LASF121
	.byte	0x4
	.byte	0x9a
	.uleb128 0x9
	.long	.LASF48
	.byte	0xc
	.byte	0x4
	.byte	0xa0
	.long	0x294
	.uleb128 0xa
	.long	.LASF49
	.byte	0x4
	.byte	0xa1
	.long	0x294
	.byte	0
	.uleb128 0xa
	.long	.LASF50
	.byte	0x4
	.byte	0xa2
	.long	0x29a
	.byte	0x4
	.uleb128 0xa
	.long	.LASF51
	.byte	0x4
	.byte	0xa6
	.long	0x5a
	.byte	0x8
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.long	0x263
	.uleb128 0x7
	.byte	0x4
	.long	0xdc
	.uleb128 0xd
	.long	0xd0
	.long	0x2b0
	.uleb128 0xe
	.long	0x30
	.byte	0
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.long	0x25c
	.uleb128 0xd
	.long	0xd0
	.long	0x2c6
	.uleb128 0xe
	.long	0x30
	.byte	0x27
	.byte	0
	.uleb128 0xf
	.long	.LASF122
	.uleb128 0x10
	.long	.LASF52
	.byte	0x4
	.value	0x13f
	.long	0x2c6
	.uleb128 0x10
	.long	.LASF53
	.byte	0x4
	.value	0x140
	.long	0x2c6
	.uleb128 0x10
	.long	.LASF54
	.byte	0x4
	.value	0x141
	.long	0x2c6
	.uleb128 0x7
	.byte	0x4
	.long	0xd7
	.uleb128 0x8
	.long	0x2ef
	.uleb128 0x11
	.long	.LASF55
	.byte	0x5
	.byte	0x87
	.long	0x29a
	.uleb128 0x11
	.long	.LASF56
	.byte	0x5
	.byte	0x88
	.long	0x29a
	.uleb128 0x11
	.long	.LASF57
	.byte	0x5
	.byte	0x89
	.long	0x29a
	.uleb128 0x11
	.long	.LASF58
	.byte	0x6
	.byte	0x1a
	.long	0x5a
	.uleb128 0xd
	.long	0x2f5
	.long	0x331
	.uleb128 0x12
	.byte	0
	.uleb128 0x8
	.long	0x326
	.uleb128 0x11
	.long	.LASF59
	.byte	0x6
	.byte	0x1b
	.long	0x331
	.uleb128 0x13
	.byte	0x80
	.byte	0x7
	.byte	0x5
	.long	0x356
	.uleb128 0xa
	.long	.LASF60
	.byte	0x7
	.byte	0x7
	.long	0x356
	.byte	0
	.byte	0
	.uleb128 0xd
	.long	0x45
	.long	0x366
	.uleb128 0xe
	.long	0x30
	.byte	0x1f
	.byte	0
	.uleb128 0x2
	.long	.LASF61
	.byte	0x7
	.byte	0x8
	.long	0x341
	.uleb128 0x2
	.long	.LASF62
	.byte	0x8
	.byte	0x7
	.long	0x366
	.uleb128 0x14
	.long	.LASF123
	.byte	0x4
	.byte	0x9
	.byte	0x18
	.long	0x39f
	.uleb128 0x15
	.long	.LASF63
	.byte	0x9
	.byte	0x1a
	.long	0x5a
	.uleb128 0x15
	.long	.LASF64
	.byte	0x9
	.byte	0x1b
	.long	0xc8
	.byte	0
	.uleb128 0x2
	.long	.LASF65
	.byte	0x9
	.byte	0x1e
	.long	0x37c
	.uleb128 0x13
	.byte	0x8
	.byte	0xa
	.byte	0x38
	.long	0x3cb
	.uleb128 0xa
	.long	.LASF66
	.byte	0xa
	.byte	0x3a
	.long	0xb2
	.byte	0
	.uleb128 0xa
	.long	.LASF67
	.byte	0xa
	.byte	0x3b
	.long	0x8a
	.byte	0x4
	.byte	0
	.uleb128 0x13
	.byte	0xc
	.byte	0xa
	.byte	0x3f
	.long	0x3f8
	.uleb128 0xa
	.long	.LASF68
	.byte	0xa
	.byte	0x41
	.long	0x5a
	.byte	0
	.uleb128 0xa
	.long	.LASF69
	.byte	0xa
	.byte	0x42
	.long	0x5a
	.byte	0x4
	.uleb128 0xa
	.long	.LASF70
	.byte	0xa
	.byte	0x43
	.long	0x39f
	.byte	0x8
	.byte	0
	.uleb128 0x13
	.byte	0xc
	.byte	0xa
	.byte	0x47
	.long	0x425
	.uleb128 0xa
	.long	.LASF66
	.byte	0xa
	.byte	0x49
	.long	0xb2
	.byte	0
	.uleb128 0xa
	.long	.LASF67
	.byte	0xa
	.byte	0x4a
	.long	0x8a
	.byte	0x4
	.uleb128 0xa
	.long	.LASF70
	.byte	0xa
	.byte	0x4b
	.long	0x39f
	.byte	0x8
	.byte	0
	.uleb128 0x13
	.byte	0x14
	.byte	0xa
	.byte	0x4f
	.long	0x46a
	.uleb128 0xa
	.long	.LASF66
	.byte	0xa
	.byte	0x51
	.long	0xb2
	.byte	0
	.uleb128 0xa
	.long	.LASF67
	.byte	0xa
	.byte	0x52
	.long	0x8a
	.byte	0x4
	.uleb128 0xa
	.long	.LASF71
	.byte	0xa
	.byte	0x53
	.long	0x5a
	.byte	0x8
	.uleb128 0xa
	.long	.LASF72
	.byte	0xa
	.byte	0x54
	.long	0xbd
	.byte	0xc
	.uleb128 0xa
	.long	.LASF73
	.byte	0xa
	.byte	0x55
	.long	0xbd
	.byte	0x10
	.byte	0
	.uleb128 0x13
	.byte	0x8
	.byte	0xa
	.byte	0x61
	.long	0x48b
	.uleb128 0xa
	.long	.LASF74
	.byte	0xa
	.byte	0x63
	.long	0xc8
	.byte	0
	.uleb128 0xa
	.long	.LASF75
	.byte	0xa
	.byte	0x64
	.long	0xc8
	.byte	0x4
	.byte	0
	.uleb128 0x16
	.byte	0x8
	.byte	0xa
	.byte	0x5e
	.long	0x4aa
	.uleb128 0x15
	.long	.LASF76
	.byte	0xa
	.byte	0x65
	.long	0x46a
	.uleb128 0x15
	.long	.LASF77
	.byte	0xa
	.byte	0x67
	.long	0x66
	.byte	0
	.uleb128 0x13
	.byte	0x10
	.byte	0xa
	.byte	0x59
	.long	0x4d7
	.uleb128 0xa
	.long	.LASF78
	.byte	0xa
	.byte	0x5b
	.long	0xc8
	.byte	0
	.uleb128 0xa
	.long	.LASF79
	.byte	0xa
	.byte	0x5d
	.long	0x53
	.byte	0x4
	.uleb128 0xa
	.long	.LASF80
	.byte	0xa
	.byte	0x68
	.long	0x48b
	.byte	0x8
	.byte	0
	.uleb128 0x13
	.byte	0x8
	.byte	0xa
	.byte	0x6c
	.long	0x4f8
	.uleb128 0xa
	.long	.LASF81
	.byte	0xa
	.byte	0x6e
	.long	0xa0
	.byte	0
	.uleb128 0xa
	.long	.LASF82
	.byte	0xa
	.byte	0x6f
	.long	0x5a
	.byte	0x4
	.byte	0
	.uleb128 0x13
	.byte	0xc
	.byte	0xa
	.byte	0x74
	.long	0x525
	.uleb128 0xa
	.long	.LASF83
	.byte	0xa
	.byte	0x76
	.long	0xc8
	.byte	0
	.uleb128 0xa
	.long	.LASF84
	.byte	0xa
	.byte	0x77
	.long	0x5a
	.byte	0x4
	.uleb128 0xa
	.long	.LASF85
	.byte	0xa
	.byte	0x78
	.long	0x30
	.byte	0x8
	.byte	0
	.uleb128 0x16
	.byte	0x74
	.byte	0xa
	.byte	0x33
	.long	0x586
	.uleb128 0x15
	.long	.LASF86
	.byte	0xa
	.byte	0x35
	.long	0x586
	.uleb128 0x15
	.long	.LASF87
	.byte	0xa
	.byte	0x3c
	.long	0x3aa
	.uleb128 0x15
	.long	.LASF88
	.byte	0xa
	.byte	0x44
	.long	0x3cb
	.uleb128 0x17
	.string	"_rt"
	.byte	0xa
	.byte	0x4c
	.long	0x3f8
	.uleb128 0x15
	.long	.LASF89
	.byte	0xa
	.byte	0x56
	.long	0x425
	.uleb128 0x15
	.long	.LASF90
	.byte	0xa
	.byte	0x69
	.long	0x4aa
	.uleb128 0x15
	.long	.LASF91
	.byte	0xa
	.byte	0x70
	.long	0x4d7
	.uleb128 0x15
	.long	.LASF92
	.byte	0xa
	.byte	0x79
	.long	0x4f8
	.byte	0
	.uleb128 0xd
	.long	0x5a
	.long	0x596
	.uleb128 0xe
	.long	0x30
	.byte	0x1c
	.byte	0
	.uleb128 0x13
	.byte	0x80
	.byte	0xa
	.byte	0x24
	.long	0x5cf
	.uleb128 0xa
	.long	.LASF93
	.byte	0xa
	.byte	0x26
	.long	0x5a
	.byte	0
	.uleb128 0xa
	.long	.LASF94
	.byte	0xa
	.byte	0x28
	.long	0x5a
	.byte	0x4
	.uleb128 0xa
	.long	.LASF95
	.byte	0xa
	.byte	0x2a
	.long	0x5a
	.byte	0x8
	.uleb128 0xa
	.long	.LASF96
	.byte	0xa
	.byte	0x7b
	.long	0x525
	.byte	0xc
	.byte	0
	.uleb128 0x2
	.long	.LASF97
	.byte	0xa
	.byte	0x7c
	.long	0x596
	.uleb128 0x2
	.long	.LASF98
	.byte	0xb
	.byte	0x48
	.long	0x5e5
	.uleb128 0x7
	.byte	0x4
	.long	0x5eb
	.uleb128 0x18
	.long	0x5f6
	.uleb128 0x19
	.long	0x5a
	.byte	0
	.uleb128 0x16
	.byte	0x4
	.byte	0xc
	.byte	0x1c
	.long	0x615
	.uleb128 0x15
	.long	.LASF99
	.byte	0xc
	.byte	0x1f
	.long	0x5da
	.uleb128 0x15
	.long	.LASF100
	.byte	0xc
	.byte	0x21
	.long	0x630
	.byte	0
	.uleb128 0x18
	.long	0x62a
	.uleb128 0x19
	.long	0x5a
	.uleb128 0x19
	.long	0x62a
	.uleb128 0x19
	.long	0xc8
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.long	0x5cf
	.uleb128 0x7
	.byte	0x4
	.long	0x615
	.uleb128 0x9
	.long	.LASF101
	.byte	0x8c
	.byte	0xc
	.byte	0x18
	.long	0x673
	.uleb128 0xa
	.long	.LASF102
	.byte	0xc
	.byte	0x23
	.long	0x5f6
	.byte	0
	.uleb128 0xa
	.long	.LASF103
	.byte	0xc
	.byte	0x2b
	.long	0x366
	.byte	0x4
	.uleb128 0xa
	.long	.LASF104
	.byte	0xc
	.byte	0x2e
	.long	0x5a
	.byte	0x84
	.uleb128 0xa
	.long	.LASF105
	.byte	0xc
	.byte	0x31
	.long	0x674
	.byte	0x88
	.byte	0
	.uleb128 0x1a
	.uleb128 0x7
	.byte	0x4
	.long	0x673
	.uleb128 0xd
	.long	0x2f5
	.long	0x68a
	.uleb128 0xe
	.long	0x30
	.byte	0x40
	.byte	0
	.uleb128 0x8
	.long	0x67a
	.uleb128 0x10
	.long	.LASF106
	.byte	0xb
	.value	0x11e
	.long	0x68a
	.uleb128 0x10
	.long	.LASF107
	.byte	0xb
	.value	0x11f
	.long	0x68a
	.uleb128 0x10
	.long	.LASF108
	.byte	0xd
	.value	0x222
	.long	0x6b3
	.uleb128 0x7
	.byte	0x4
	.long	0xca
	.uleb128 0x11
	.long	.LASF109
	.byte	0xe
	.byte	0x24
	.long	0xca
	.uleb128 0x11
	.long	.LASF110
	.byte	0xe
	.byte	0x32
	.long	0x5a
	.uleb128 0x11
	.long	.LASF111
	.byte	0xe
	.byte	0x37
	.long	0x5a
	.uleb128 0x11
	.long	.LASF112
	.byte	0xe
	.byte	0x3b
	.long	0x5a
	.uleb128 0x1b
	.long	.LASF113
	.byte	0x1
	.byte	0x6
	.long	0x61
	.uleb128 0x5
	.byte	0x3
	.long	counter
	.uleb128 0x1c
	.long	.LASF124
	.byte	0x1
	.byte	0x16
	.long	0x5a
	.long	.LFB6
	.long	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.long	0x74a
	.uleb128 0x1d
	.long	.LASF114
	.byte	0x1
	.byte	0x16
	.long	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1d
	.long	.LASF115
	.byte	0x1
	.byte	0x16
	.long	0x6b3
	.uleb128 0x3
	.byte	0x75
	.sleb128 -300
	.uleb128 0x1e
	.string	"sa"
	.byte	0x1
	.byte	0x1b
	.long	0x636
	.uleb128 0x3
	.byte	0x75
	.sleb128 -168
	.uleb128 0x1f
	.long	.LASF116
	.byte	0x1
	.byte	0x20
	.long	0x371
	.uleb128 0x3
	.byte	0x75
	.sleb128 -296
	.byte	0
	.uleb128 0x20
	.long	.LASF125
	.byte	0x1
	.byte	0x8
	.long	.LFB5
	.long	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x1d
	.long	.LASF117
	.byte	0x1
	.byte	0x8
	.long	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x17
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x15
	.byte	0
	.uleb128 0x27
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x1c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.value	0
	.value	0
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF12:
	.string	"__off_t"
.LASF19:
	.string	"_IO_read_ptr"
.LASF77:
	.string	"_pkey"
.LASF31:
	.string	"_chain"
.LASF6:
	.string	"size_t"
.LASF78:
	.string	"si_addr"
.LASF94:
	.string	"si_errno"
.LASF37:
	.string	"_shortbuf"
.LASF104:
	.string	"sa_flags"
.LASF54:
	.string	"_IO_2_1_stderr_"
.LASF25:
	.string	"_IO_buf_base"
.LASF118:
	.string	"GNU C11 7.5.0 -m32 -mtune=generic -march=i686 -g -fstack-protector-strong"
.LASF98:
	.string	"__sighandler_t"
.LASF74:
	.string	"_lower"
.LASF9:
	.string	"long long unsigned int"
.LASF73:
	.string	"si_stime"
.LASF85:
	.string	"_arch"
.LASF65:
	.string	"__sigval_t"
.LASF8:
	.string	"long long int"
.LASF4:
	.string	"signed char"
.LASF32:
	.string	"_fileno"
.LASF20:
	.string	"_IO_read_end"
.LASF89:
	.string	"_sigchld"
.LASF10:
	.string	"__quad_t"
.LASF107:
	.string	"sys_siglist"
.LASF13:
	.string	"long int"
.LASF28:
	.string	"_IO_backup_base"
.LASF18:
	.string	"_flags"
.LASF26:
	.string	"_IO_buf_end"
.LASF35:
	.string	"_cur_column"
.LASF75:
	.string	"_upper"
.LASF69:
	.string	"si_overrun"
.LASF80:
	.string	"_bounds"
.LASF34:
	.string	"_old_offset"
.LASF39:
	.string	"_offset"
.LASF79:
	.string	"si_addr_lsb"
.LASF70:
	.string	"si_sigval"
.LASF62:
	.string	"sigset_t"
.LASF7:
	.string	"__uint32_t"
.LASF116:
	.string	"mask"
.LASF14:
	.string	"__off64_t"
.LASF123:
	.string	"sigval"
.LASF66:
	.string	"si_pid"
.LASF48:
	.string	"_IO_marker"
.LASF55:
	.string	"stdin"
.LASF0:
	.string	"unsigned int"
.LASF60:
	.string	"__val"
.LASF72:
	.string	"si_utime"
.LASF3:
	.string	"long unsigned int"
.LASF122:
	.string	"_IO_FILE_plus"
.LASF23:
	.string	"_IO_write_ptr"
.LASF61:
	.string	"__sigset_t"
.LASF58:
	.string	"sys_nerr"
.LASF50:
	.string	"_sbuf"
.LASF2:
	.string	"short unsigned int"
.LASF67:
	.string	"si_uid"
.LASF97:
	.string	"siginfo_t"
.LASF27:
	.string	"_IO_save_base"
.LASF63:
	.string	"sival_int"
.LASF119:
	.string	"main.c"
.LASF16:
	.string	"__clock_t"
.LASF38:
	.string	"_lock"
.LASF92:
	.string	"_sigsys"
.LASF33:
	.string	"_flags2"
.LASF45:
	.string	"_mode"
.LASF56:
	.string	"stdout"
.LASF84:
	.string	"_syscall"
.LASF52:
	.string	"_IO_2_1_stdin_"
.LASF86:
	.string	"_pad"
.LASF109:
	.string	"optarg"
.LASF91:
	.string	"_sigpoll"
.LASF110:
	.string	"optind"
.LASF120:
	.string	"/home/asus/sm/sm19-1"
.LASF96:
	.string	"_sifields"
.LASF24:
	.string	"_IO_write_end"
.LASF117:
	.string	"signo"
.LASF101:
	.string	"sigaction"
.LASF121:
	.string	"_IO_lock_t"
.LASF47:
	.string	"_IO_FILE"
.LASF68:
	.string	"si_tid"
.LASF108:
	.string	"__environ"
.LASF57:
	.string	"stderr"
.LASF51:
	.string	"_pos"
.LASF59:
	.string	"sys_errlist"
.LASF30:
	.string	"_markers"
.LASF90:
	.string	"_sigfault"
.LASF1:
	.string	"unsigned char"
.LASF76:
	.string	"_addr_bnd"
.LASF15:
	.string	"__pid_t"
.LASF5:
	.string	"short int"
.LASF113:
	.string	"counter"
.LASF83:
	.string	"_call_addr"
.LASF36:
	.string	"_vtable_offset"
.LASF53:
	.string	"_IO_2_1_stdout_"
.LASF71:
	.string	"si_status"
.LASF112:
	.string	"optopt"
.LASF17:
	.string	"char"
.LASF125:
	.string	"func"
.LASF114:
	.string	"argc"
.LASF111:
	.string	"opterr"
.LASF11:
	.string	"__uid_t"
.LASF49:
	.string	"_next"
.LASF102:
	.string	"__sigaction_handler"
.LASF93:
	.string	"si_signo"
.LASF21:
	.string	"_IO_read_base"
.LASF87:
	.string	"_kill"
.LASF29:
	.string	"_IO_save_end"
.LASF106:
	.string	"_sys_siglist"
.LASF100:
	.string	"sa_sigaction"
.LASF103:
	.string	"sa_mask"
.LASF40:
	.string	"__pad1"
.LASF41:
	.string	"__pad2"
.LASF42:
	.string	"__pad3"
.LASF43:
	.string	"__pad4"
.LASF44:
	.string	"__pad5"
.LASF46:
	.string	"_unused2"
.LASF105:
	.string	"sa_restorer"
.LASF115:
	.string	"argv"
.LASF88:
	.string	"_timer"
.LASF82:
	.string	"si_fd"
.LASF99:
	.string	"sa_handler"
.LASF64:
	.string	"sival_ptr"
.LASF81:
	.string	"si_band"
.LASF124:
	.string	"main"
.LASF22:
	.string	"_IO_write_base"
.LASF95:
	.string	"si_code"
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits