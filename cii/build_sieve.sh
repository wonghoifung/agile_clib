#as -o swtch.o swtch.s
#cc -c -o swtch.o swtch.s 
cc -g -c -o swtch.o swtch2.S
cc -g -c -o thread.o thread.c
cc -g -c -o mem.o mem.c
cc -g -c -o fmt.o fmt.c
cc -g -c -o assert.o assert.c
cc -g -c -o except.o except.c
cc -g -c -o chan.o chan.c
ar ruv libcii.a mem.o fmt.o assert.o except.o thread.o swtch.o chan.o
cc -g -c -o sieve.o sieve.c
cc -g -o sieve sieve.o libcii.a

