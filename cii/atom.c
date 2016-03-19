// includes
#include "atom.h"
#include <string.h>
#if 0
#include "assert.h"
#else
#include <assert.h>
#endif
#include <limits.h>

// macros

// data
static struct atom {
	struct atom* link;
	int len;
	char* str;
}* buckets[2048];

// functions
const char* Atom_string(const char* str) {
	assert(str);
	return Atom_new(str, strlen(str));
}

const char* Atom_int(long n) {
	char str[43];
	char* s = str + sizeof str;
	unsigned long m;
	if (n == LONG_MIN)
		m = LONG_MAX + 1UL;
	else if (n < 0)
		m = -n;
	else 
		m = n;
	do 
		*--s = m % 10 + '0';
	while ((m /= 10) > 0);
	if (n < 0)
		*--s = '-';
	return Atom_new(s, (str + sizeof str) - s);
}