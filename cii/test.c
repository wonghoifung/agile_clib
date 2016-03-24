// #include "arith.h"
// #include "stack.h"
// #include "atom.h"
// #include "except.h"
// #include "assert.h"
// #include "mem.h"
// #include "arena.h"
#include "list.h"
#include <stdio.h>
#include <string.h>

// Except_T ee = { "hello exception" };

void print(void** x, void* cl) {
	char** str = (char**)x;
	FILE* fp = cl;
	fprintf(fp, "%s\n", *str);
}

int main() {

	List_T p1, p2;
	p1 = List_list(NULL);
	p2 = List_list("Atom", "Mem", "Arena", "List", NULL);
	List_map(p2, print, stderr);
	p2 = List_append(p2, List_list("Except", NULL));
	printf("\n");
	List_map(p2, print, stderr);

#if 0
	Arena_T arena = Arena_new();
	
	char* s1 = AALLOC(arena, 10);
	memcpy(s1, "hello", 5);

	char* s2 = AALLOC(arena, 10);
	memcpy(s2, "world", 5);

	printf("%s %s\n", s1, s2);

	Arena_dispose(&arena);
#endif

#if 0
	char* buf = ALLOC(1024);
	FREE(buf);
#endif

#if 0
	//(assert)(1 == 0);
	assert(1 == 2);
#endif

#if 0
	TRY		
		RAISE(ee);
	EXCEPT(ee)
		printf("handled\n");
	END_TRY;
#endif

#if 0
	const char* atom1 = Atom_string("hello");
	const char* atom2 = Atom_int(12345);
	printf("atom1:%s, atom2:%s\n", atom1, atom2);
	printf("%d, %d\n", Atom_length(atom1), Atom_length(atom2));
#endif

#if 0
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
#endif

#if 0
	Stack_T st = Stack_new();
	printf("empty:%d\n", Stack_empty(st));
	Stack_push(st, (void*)123);
	Stack_push(st, (void*)456);
	printf("empty:%d\n", Stack_empty(st));
	printf("%ld\n", (long)Stack_pop(st));
	printf("%ld\n", (long)Stack_pop(st));
	Stack_free(&st);
#endif


	return 0;
}
