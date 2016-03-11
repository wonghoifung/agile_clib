#include "arith.h"
#include <stdio.h>

int main() {
	int x = -13;
	int y = 5;
	printf("%d\n", Arith_div(x,y));
	printf("%d\n", x/y);
	
	int N = 10;
	printf("%d\n", Arith_mod(10,N));
	printf("%d\n", Arith_mod(11,N));
	printf("%d\n", Arith_mod(0-1,N));

	printf("%d\n", (10%N));
	printf("%d\n", (11%N));
	printf("%d\n", ((0-1)%N));
	return 0;
}
