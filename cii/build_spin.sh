#as -o swtch.o swtch.s
#cc -c -o swtch.o swtch.s 
cc -c -o swtch.o swtch2.S
cc -c -o thread.o thread.c
cc -c -o mem.o mem.c
cc -c -o fmt.o fmt.c
cc -c -o assert.o assert.c
cc -c -o except.o except.c
cc -c -o chan.o chan.c
ar ruv libcii.a mem.o fmt.o assert.o except.o thread.o swtch.o chan.o
cc -g -c -o spin.o spin.c
cc -g -o spin spin.o libcii.a

