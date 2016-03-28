#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "assert.h"
#include "ring.h"
#include "mem.h"

#define T Ring_T

struct T {
	struct node {
		struct node *llink, *rlink;
		void* value;
	}* head;
	int length;
};

// functions


