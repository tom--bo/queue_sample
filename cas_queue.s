	.file	"cas_queue.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN22UnBoundedLockFreeQueue5enqueEl
	.type	_ZN22UnBoundedLockFreeQueue5enqueEl, @function
_ZN22UnBoundedLockFreeQueue5enqueEl:
.LFB340:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	movl	$16, %edi
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	call	_Znwm@PLT
	leaq	8(%rbx), %rdi
	movl	$5, %ecx
	movq	$0, 8(%rax)
	movq	%rax, %r8
	movq	%rbp, (%rax)
.L7:
	movq	(%rdi), %rdx
	leaq	8(%rdx), %r10
	movq	8(%rdx), %r9
	movq	(%rdi), %rsi
	cmpq	%rsi, %rdx
	je	.L14
.L3:
	subl	$1, %ecx
	jne	.L7
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L14:
	.cfi_restore_state
	testq	%r9, %r9
	jne	.L4
	movq	%r9, %rax
	lock cmpxchgq	%r8, (%r10)
	jne	.L3
	movq	%rdx, %rax
	lock cmpxchgq	%r8, (%rdi)
	movl	$1, %eax
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	.cfi_restore_state
	movq	%rdx, %rax
	lock cmpxchgq	%r9, (%rdi)
	jmp	.L3
	.cfi_endproc
.LFE340:
	.size	_ZN22UnBoundedLockFreeQueue5enqueEl, .-_ZN22UnBoundedLockFreeQueue5enqueEl
	.align 2
	.p2align 4
	.globl	_ZN22UnBoundedLockFreeQueue5dequeERl
	.type	_ZN22UnBoundedLockFreeQueue5dequeERl, @function
_ZN22UnBoundedLockFreeQueue5dequeERl:
.LFB341:
	.cfi_startproc
	endbr64
	leaq	8(%rdi), %r10
	xorl	%r8d, %r8d
	movq	(%rdi), %rax
	movq	8(%rdi), %r9
	movq	8(%rax), %rcx
	movq	(%rdi), %rdx
	cmpq	%rdx, %rax
	je	.L21
.L15:
	movl	%r8d, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L21:
	cmpq	%r9, %rax
	je	.L22
	movq	(%rcx), %rdx
	movq	%rdx, (%rsi)
	lock cmpxchgq	%rcx, (%rdi)
	sete	%r8b
	movl	%r8d, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L22:
	testq	%rcx, %rcx
	je	.L15
	lock cmpxchgq	%rcx, (%r10)
	jmp	.L15
	.cfi_endproc
.LFE341:
	.size	_ZN22UnBoundedLockFreeQueue5dequeERl, .-_ZN22UnBoundedLockFreeQueue5dequeERl
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
