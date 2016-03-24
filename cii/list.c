#include <stdarg.h>
#include <stddef.h>
#include "assert.h"
#include "mem.h"
#include "list.h"

#define T List_T

// functions
T List_push(T list, void* x) {
	T p;
	NEW(p);
	p->first = x;
	p->rest = list;
	return p;
}

T List_list(void* x, ...) {
	va_list ap;
	T list, *p = &list;
	va_start(ap, x);
	for (; x; x=va_arg(ap, void*)) {
		NEW(*p);
		(*p)->first = x;
		p = &(*p)->rest;
	}
	*p = NULL;
	va_end(ap);
	return list;
}