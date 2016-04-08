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
	movl	20(%esp),%eax # eax = from
	movl	%esp,0(%eax)  # from->sp = esp
	movl	24(%esp),%eax # eax = to
	movl	0(%eax),%esp  # esp = to->sp
	movl	0(%esp),%ebx  # ebx = *(to->sp)
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
.align	8
.globl	__swtch
.globl	_swtch
__swtch:
_swtch:
	subq	$32,%rsp
	movq	%rbx,0(%rsp)
	movq	%rsi,8(%rsp)
	movq	%rdi,16(%rsp)
	movq	%rbp,24(%rsp)
	movq	%rdi,%rax     # rax = from
	movq	%rsp,0(%rax)  # from->sp = rsp
	movq	%rsi,%rax     # rax = to
	movq	0(%rax),%rsp  # rsp = to->sp
	movq	0(%rsp),%rbx  # rbx = *(to->sp)
	movq	8(%rsp),%rsi
	movq	16(%rsp),%rdi
	movq	24(%rsp),%rbp
	addq	$32, %rsp
	ret
.align	8
.globl	__thrstart
.globl	_thrstart
__thrstart:
_thrstart:
	#pushq	%rdi # stack is 32-byte aligned after this push
	call	*%rsi
	#subq    $24,%rsp # ensure stack is 32-byte aligned before the call
	#pushq	%rax
	movq 	%rax,%rdi
	call	Thread_exit
.globl	__ENDMONITOR
.globl	_ENDMONITOR
__ENDMONITOR:
_ENDMONITOR:
#else
unsupported platform
#endif