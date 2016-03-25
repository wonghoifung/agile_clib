// #include "arith.h"
// #include "stack.h"
// #include "atom.h"
// #include "except.h"
// #include "assert.h"
// #include "mem.h"
// #include "arena.h"
// #include "list.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "atom.h"
#include "table.h"
#include "mem.h"
#include "getword.h"

// Except_T ee = { "hello exception" };

// void print(void** x, void* cl) {
// 	char** str = (char**)x;
// 	FILE* fp = cl;
// 	fprintf(fp, "%s\n", *str);
// }

int first(int c) { return isalpha(c); }

int rest(int c) { return isalpha(c) || c=='_'; }

int compare(const void* x, const void* y) { return strcmp(*(char**)x, *(char**)y); }

void vfree(const void* key, void** count, void* cl) { FREE(*count); }

void wf(char* name, FILE* fp) {
	Table_T table = Table_new(0, NULL, NULL);
	char buf[128];
	while (getword(fp, buf, sizeof buf, first, rest)) {
		const char* word;
		int i, *count;
		for (i = 0; buf[i] != '\0'; i++)
			buf[i] = tolower(buf[i]);
		word = Atom_string(buf);
		count = Table_get(table, word);
		if (count)
			(*count)++;
		else {
			NEW(count);
			*count = 1;
			Table_put(table, word, count);
		}
	}
	
	if (name)
		printf("%s:\n", name);

	{
		// print the words
		int i;
		void** array = Table_toArray(table, NULL);
		qsort(array, Table_length(table), 2 * sizeof (*array), compare);
		for (i=0; array[i]; i+=2)
			printf("%d\t%s\n", *(int*)array[i+1], (char*)array[i]);
		FREE(array);
	}

	// deallocate the entries and table
	Table_map(table, vfree, NULL);
	Table_free(&table);
}

int main() {

	int i;
	for (i=1; i<argc; ++i) {
		FILE* fp = fopen(argv[i],"r");
		if (fp==NULL) {
			fprintf(stderr, "%s: can't open '%s' (%s)\n", argv[0], argv[i], strerror(errno));
			return EXIT_FAILURE;
		} else {
			wf(argv[i], fp);
			fclose(fp);
		}
	}
	if (argc==1) wf(NULL, stdin);
	return EXIT_SUCCESS;

#if 0
	List_T p1, p2;
	p1 = List_list(NULL);
	p2 = List_list("Atom", "Mem", "Arena", "List", NULL);
	List_map(p2, print, stderr);
	p2 = List_append(p2, List_list("Except", NULL));
	printf("\n");
	List_map(p2, print, stderr);
	List_free(&p1);
	List_free(&p2);
#endif

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
