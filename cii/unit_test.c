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

	#if X86_FXSR_MAGIC
	{
		printf("MAGIC\n");
	}
	#endif

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
	// #elif __i386__
	// {
	// 	printf("__i386__\n");
	// }
	#elif linux && i386
	{
		printf("linux && i386\n");
	}
	// #elif __amd64
	// {
	// 	printf("__amd64\n");
	// }
	#elif __x86_64__
	{
		printf("__x86_64__\n");
	}
	#else
	unsupported platform
	#endif
}
