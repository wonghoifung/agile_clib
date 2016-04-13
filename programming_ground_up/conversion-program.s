.include "linux.s"

.section .data

tmp_buffer:
	.ascii "\0\0\0\0\0\0\0\0\0\0\0"

.section .text

.globl _start
_start:
	movl %esp, %ebp
	# storage for the result
	pushl $tmp_buffer
	# number to convert
	pushl $824
	call integer2string
	addl $8, %esp
	# char count
	pushl $tmp_buffer
	call count_chars
	addl $4, %esp
	# count goes in %edx for SYS_WRITE
	movl %eax, %edx
	movl $SYS_WRITE, %eax
	movl $STDOUT, %ebx
	movl $tmp_buffer, %ecx
	int $LINUX_SYSCALL
	pushl $STDOUT
	call write_newline
	movl $SYS_EXIT, %eax
	movl $0, %ebx
	int $LINUX_SYSCALL
	