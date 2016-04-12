.section .data

head_begin:
	.long 0
current_break:
	.long 0

.equ HEADER_SIZE, 8
.equ HDR_AVAIL_OFFSET, 0
.equ HDR_SIZE_OFFSET, 4

.equ UNAVAILABLE, 0
.equ AVAILABLE, 1
.equ SYS_BRK, 45
.equ LINUX_SYSCALL, 0x80

.section .text

# intf allocate_init
.globl allocate_init
.type allocate_init, @function
allocate_init:
	pushl %ebp
	movl %esp, %ebp
	# find out where the break is
	movl $SYS_BRK, %eax
	movl $0, %ebx
	int $LINUX_SYSCALL
	# %eax now has the last valid address, and we want mem loc after that
	# init current_break heap_begin
	incl %eax
	movl %eax, current_break
	movl %eax, heap_begin
	# return 
	movl %ebp, %esp
	popl %ebp
	ret

# intf allocate 
# reg used: %ecx - requested size 
#           %eax - current mem region being examined
#           %ebx - current break position
#           %edx - size of current mem region
.globl allocate
.type allocate, @function
.equ ST_MEM_SIZE, 8
allocate:
	pushl %ebp
	movl %esp, %ebp
	# %ecx - requested size
	movl ST_MEM_SIZE(%ebp), %ecx
	# %eax hold the current search location
	movl heap_begin, %eax
	# %ebx hold the current break
	movl current_break, %ebx
allocate_loop_begin:
	cmpl %ebx, %eax
	je move_break
	# grab the size of this memory
	movl HDR_SIZE_OFFSET(%eax), %edx
	# is it available?
	cmpl $UNAVAILABLE, HDR_AVAIL_OFFSET(%eax)
	je next_location
	# is the size big enough?
	cmpl %edx, %ecx
	jle allocate_here # %ecx <= %edx, enough!
next_location:
	# get the address of the next memory region
	addl $HEADER_SIZE, %eax
	addl %edx, %eax
	jmp allocate_loop_begin
allocate_here:
	movl $UNAVAILABLE, HDR_AVAIL_OFFSET(%eax)
	addl $HEADER_SIZE, %eax
	movl %ebp, %esp
	popl %ebp
	ret
move_break:
	addl $HEADER_SIZE, %ebx
	addl %ecx, %ebx
	# save regs before ask linux for more memory
	pushl %eax
	pushl %ecx
	pushl %ebx
	movl $SYS_BRK, %eax # %ebx has the requested brk point
	int $LINUX_SYSCALL 
	cmpl $0, %eax # don't care where it actually sets the break,
	je error      # as long as %eax isn't 0, %eax is the new break
	# restore saved regs
	popl %ebx
	popl %ecx
	popl %eax
	# %eax is now the last break, give it away
	movl $UNAVAILABLE, HDR_AVAIL_OFFSET(%eax)
	movl %ecx, HDR_SIZE_OFFSET(%eax)
	addl $HEADER_SIZE, %eax
	# save the new break in theory...
	movl %ebx, current_break
	# return
	movl %ebp, %esp
	popl %ebp
	ret
error:
	movl $0, %eax
	movl %ebp, %esp
	popl %ebp
	ret

# intf deallocate
.globl deallocate
.type deallocate, @function
.equ ST_MEMORY_SEG, 4
deallocate:
	movl ST_MEMORY_SEG(%esp), %eax
	subl $HEADER_SIZE, %eax
	movl $AVAILABLE, HDR_AVAIL_OFFSET(%eax)
	ret

