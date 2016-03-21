#ifndef EXCEPT_HEADER
#define EXCEPT_HEADER

#include <setjmp.h>

#define T Except_T

typedef struct T {
	const char* reason;
} T;

// types

// variables

// functions
void Except_raise(const T* e, const char* file, int line);

// macros
#define RAISE(e) Except_raise(&(e), __FILE__, __LINE__)

#endif
