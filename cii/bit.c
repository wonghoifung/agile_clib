#include <stdarg.h>
#include <string.h>
#include "assert.h"
#include "bit.h"
#include "mem.h"

#define T Bit_T

struct T {
	int length;
	unsigned char* bytes;
	unsigned long* words;
};

// macros
#define BPW (8 * sizeof (unsigned long))
#define nwords(len) ((((len) + BPW - 1) & (~(BPW - 1))) / BPW)

// static data

// static functions

// functions
T Bit_new(int length) {
	T set;
	assert(length >= 0);
	NEW(set);
	if (length > 0)
		set->words = CALLOC(nwords(length), sizeof (unsigned long));
	else 
		set->words = NULL;
	set->bytes = (unsigned char*)set->words;
	set->length = length;
	return set;
}

void Bit_free(T* set) {
	assert(set && *set);
	FREE((*set)->words);
	FREE(*set);
}

int Bit_length(T set) {
	assert(set);
	return set->length;
}

