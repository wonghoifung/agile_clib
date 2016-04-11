.section .data

info:
	.string "hello world\n"
	info_len = . - info

.equ SYS_WRITE, 4
.equ SYS_EXIT, 1

.equ STDOUT, 1

.equ LINUX_SYSCALL, 0x80

.section .text

.global _start
_start:
	movq $info_len, %rdx
	movq $SYS_WRITE, %rax
	movq $STDOUT, %rbx
	movq $info, %rcx
	int $LINUX_SYSCALL

	movq $SYS_EXIT, %rax
	movq $0, %rbx
	int $LINUX_SYSCALL
