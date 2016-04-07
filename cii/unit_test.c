// #include "array.h"
// #include "seq.h"
// #include "ring.h"
// #include "bit.h"
// #include "fmt.h"
// #include "text.h"

#include <stdio.h>

int main() {
	// test_array();
	// test_seq();
	// test_ring();
	// test_bit();
	// test_fmt();
	// test_text();

	#if alpha
	{
		printf("alpha\n");
	}
	#elif mips
	{
		printf("mips\n");
	}
	#elif sparc
	{
		printf("sparc\n");
	}
	#elif linux && i386
	{
		printf("linux && i386\n");
	}
	#else
	unsupported platform
	#endif
}
