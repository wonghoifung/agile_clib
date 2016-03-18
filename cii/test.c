// #include "arith.h"
#include "stack.h"
#include <stdio.h>

int main() {
	// int x = -13;
	// int y = 5;
	// printf("%d\n", Arith_div(x,y));
	// printf("%d\n", x/y);
	
	// int N = 10;
	// printf("%d\n", Arith_mod(10,N));
	// printf("%d\n", Arith_mod(11,N));
	// printf("%d\n", Arith_mod(0-1,N));

	// printf("%d\n", (10%N));
	// printf("%d\n", (11%N));
	// printf("%d\n", ((0-1)%N));

	Stack_T st = Stack_new();
	printf("empty:%d\n", Stack_empty(st));
	Stack_push(st, (void*)123);
	Stack_push(st, (void*)456);
	printf("empty:%d\n", Stack_empty(st));
	printf("%ld\n", (long)Stack_pop(st));
	printf("%ld\n", (long)Stack_pop(st));
	Stack_free(&st);

	return 0;
}
