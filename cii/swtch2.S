#if linux && i386
.align	4
.globl	__swtch
.globl	_swtch
__swtch:
_swtch:
	subl	$16,%esp
	movl	%ebx,0(%esp)
	movl	%esi,4(%esp)
	movl	%edi,8(%esp)
	movl	%ebp,12(%esp)
	movl	20(%esp),%eax # %eax = from
	movl	%esp,0(%eax)  # from->sp = %esp
	movl	24(%esp),%eax # %eax = to
	movl	0(%eax),%esp  # %esp = to->sp
	movl	0(%esp),%ebx  # %ebx = *(to->sp)
	movl	4(%esp),%esi
	movl	8(%esp),%edi
	movl	12(%esp),%ebp
	addl	$16, %esp
	ret
.align	4
.globl	__thrstart
.globl	_thrstart
__thrstart:
_thrstart:
	pushl	%edi # stack is 16-byte aligned after this push
	call	*%esi
	subl    $12,%esp # ensure stack is 16-byte aligned before the call
	pushl	%eax
	call	Thread_exit
.globl	__ENDMONITOR
.globl	_ENDMONITOR
__ENDMONITOR:
_ENDMONITOR:
#elif linux && __x86_64__

#define PRINT 1

#if PRINT
.section .data

info:
	.string "in _thrstart\n"
info_len = . - info

.equ SYS_WRITE, 4
.equ SYS_EXIT, 1

.equ STDOUT, 1

.equ LINUX_SYSCALL, 0x80

.section .text
#endif

.align	8
.globl	__swtch
.globl	_swtch
__swtch:
_swtch:
	# subq	$32,%rsp
	subq	$96,%rsp

	movq	%rbx,0(%rsp)
	movq	%rsi,8(%rsp)
	movq	%rdi,16(%rsp)
	movq	%rbp,24(%rsp)

	movq	%r10,32(%rsp)
	movq	%r11,40(%rsp)
	movq	%r12,48(%rsp)
	movq	%r13,56(%rsp)
	movq	%r14,64(%rsp)
	movq	%r15,72(%rsp)
	movq	%r8,80(%rsp)
	movq	%r9,88(%rsp)

	movq	%rdi,%rax     # %rax = from
	movq	%rsp,0(%rax)  # from->sp = %rsp
	movq	%rsi,%rax     # %rax = to
	movq	0(%rax),%rsp  # %rsp = to->sp
	movq	0(%rsp),%rbx  # %rbx = *(to->sp)
	movq	8(%rsp),%rsi
	movq	16(%rsp),%rdi
	movq	24(%rsp),%rbp

	movq	32(%rsp),%r10
	movq	40(%rsp),%r11
	movq	48(%rsp),%r12
	movq	56(%rsp),%r13
	movq	64(%rsp),%r14
	movq	72(%rsp),%r15
	movq	80(%rsp),%r8
	movq	88(%rsp),%r9

	# addq	$32, %rsp
	addq	$96, %rsp
	ret
.align	8
.globl	__thrstart
.globl	_thrstart
__thrstart:
_thrstart:

	call	*%rsi
	movq 	%rax,%rdi

	###############
#if PRINT
	pushq %rsi
	pushq %rdi
	movq $info_len, %rdx
	movq $SYS_WRITE, %rax
	movq $STDOUT, %rbx
	movq $info, %rcx
	int $LINUX_SYSCALL
	popq %rdi
	popq %rsi
#endif
	###############

	call	Thread_exit
.globl	__ENDMONITOR
.globl	_ENDMONITOR
__ENDMONITOR:
_ENDMONITOR:
#else
unsupported platform
#endif