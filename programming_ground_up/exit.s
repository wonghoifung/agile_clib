.section .data

.section .text
.global _start
_start:
	movl $1, %eax # linux kernel command number(syscall) for exiting a program
	movl $0, %ebx # status return to os, check by echo $?
	int $0x80 # wakes up the kernel to run the exit command
