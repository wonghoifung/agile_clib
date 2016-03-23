#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "except.h"
#include "mem.h"

// checking types

// checking macros
#define hash(p, t) (((unsigned long)(p)>>3) & (sizeof (t)/sizeof ((t)[0]) - 1))

// data

// checking data
static struct descriptor {
	struct descriptor* free;
	struct descriptor* link;
	const void* ptr;
	long size;
	const char* file;
	int line;
}* htab[2048];

static struct descriptor freelist = { &freelist };

// checking functions
static struct descriptor* find(const void* ptr) {
	struct descriptor* bp = htab[hash(ptr, htab)];
	while (bp && bp->ptr != ptr)
		bp = bp->link;
	return bp;
}