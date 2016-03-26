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
	
	struct binding {
		struct binding* link;
		const void* key;
		void* value;
	}** buckets;
};

// static functions

// functions