	.file	"lock_queue.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN23UnBoundedMutexLockQueue5enqueEl
	.type	_ZN23UnBoundedMutexLockQueue5enqueEl, @function
_ZN23UnBoundedMutexLockQueue5enqueEl:
.LFB350:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rsi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	movl	$16, %edi
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	call	_Znwm@PLT
	movq	%rbp, %rdi
	movq	%r12, (%rax)
	movq	%rax, %rbx
	movq	$0, 8(%rax)
	call	pthread_mutex_lock@PLT
	movq	144(%rbp), %rax
	movq	%rbx, 8(%rax)
	movl	$1, %eax
	movq	%rbx, 144(%rbp)
	lock xaddl	%eax, 128(%rbp)
	movq	%rbp, %rdi
	testl	%eax, %eax
	jne	.L5
	call	pthread_mutex_unlock@PLT
	leaq	40(%rbp), %r12
	movq	%r12, %rdi
	call	pthread_mutex_lock@PLT
	leaq	80(%rbp), %rdi
	call	pthread_cond_broadcast@PLT
	movq	%r12, %rdi
.L5:
	call	pthread_mutex_unlock@PLT
	popq	%rbx
	.cfi_def_cfa_offset 24
	movl	$1, %eax
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE350:
	.size	_ZN23UnBoundedMutexLockQueue5enqueEl, .-_ZN23UnBoundedMutexLockQueue5enqueEl
	.align 2
	.p2align 4
	.globl	_ZN23UnBoundedMutexLockQueue5dequeERl
	.type	_ZN23UnBoundedMutexLockQueue5dequeERl, @function
_ZN23UnBoundedMutexLockQueue5dequeERl:
.LFB351:
	.cfi_startproc
	endbr64
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	movq	%rsi, %r14
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rdi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	leaq	80(%r13), %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	leaq	40(%rdi), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rbp, %rdi
	leaq	128(%r13), %rbx
	call	pthread_mutex_lock@PLT
	jmp	.L9
	.p2align 4,,10
	.p2align 3
.L11:
	movq	%rbp, %rsi
	movq	%r12, %rdi
	call	pthread_cond_wait@PLT
.L9:
	movl	(%rbx), %eax
	testl	%eax, %eax
	je	.L11
	movq	136(%r13), %rax
	movq	8(%rax), %rax
	movq	(%rax), %rdx
	movq	%rdx, (%r14)
	movq	%rax, 136(%r13)
	lock subl	$1, (%rbx)
	movq	%rbp, %rdi
	call	pthread_mutex_unlock@PLT
	popq	%rbx
	.cfi_def_cfa_offset 40
	movl	$1, %eax
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE351:
	.size	_ZN23UnBoundedMutexLockQueue5dequeERl, .-_ZN23UnBoundedMutexLockQueue5dequeERl
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
