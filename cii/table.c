#include <limits.h>
#include <stddef.h>
#include "mem.h"
#include "assert.h"
#include "table.h"

#define T Table_T

// types
struct T {
	// fields
	int size;
	int (*cmp)(const void* x, const void* y);
	unsigned (*hash)(const void* key);
	int length;
	unsigned timestamp;

	struct binding {
		struct binding* link;
		const void* key;
		void* value;
	}** buckets;
};

// static functions
static int cmpatom(const void* x, const void* y) { return x != y; }

static unsigned hashatom(const void* key) { return (unsigned long)key >> 2; }

// functions
T Table_new(int hint, int cmp(const void* x, const void* y), unsigned hash(const void* key)) {
	T table;
	int i;
	static int primes[] = { 509, 509, 1021, 2053, 4093, 8191, 16381, 32771, 65521, INT_MAX };
	assert(hint >= 0);
	for (i=1; primes[i]<hint; i++) 
		;
	table = ALLOC(sizeof (*table) + primes[i-1] * sizeof (table->buckets[0]));
	table->size = primes[i-1];
	table->cmp = cmp ? cmp : cmpatom;
	table->hash = hash ? hash : hashatom;
	table->buckets = (struct binding**)(table + 1);
	for (i=0; i<table->size; i++)
		table->buckets[i] = NULL;
	table->length = 0;
	table->timpstamp = 0;
	return table;
}
