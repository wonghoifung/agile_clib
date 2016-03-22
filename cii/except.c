#include <stdlib.h>
#include <stdio.h>
#if 0
#include "assert.h"
#else
#include <assert.h>
#endif
#include "except.h"

#define T Except_T

Except_Frame* Except_stack = NULL;

void Except_raise(const T* e, const char* file, int line) {
	Except_Frame* p = Except_stack;
	assert(e);
	if (p == NULL) {
		// announce an uncaught exception
		fprintf(stderr, "uncaught exception");
		if (e->reason)
			fprintf(stderr, " %s", e->reason);
		else 
			fprintf(stderr, " at 0X%p", e);
		if (file && line > 0)
			fprintf(stderr, " raised at %s:%d\n", file, line);
		fprintf(stderr, "aborting...\n");
		fflush(stderr);
		abort();
	}
	p->exception = e;
	p->file = file;
	p->line = line;
	Except_stack = Except_stack->prev;
	longjmp(p->env, Except_raised);
}
