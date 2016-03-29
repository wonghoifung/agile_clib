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
T Ring_new(void) {
	T ring;
	NEW0(ring);
	ring->head = NULL;
	return ring;
}

T Ring_ring(void* x, ...) {
	va_list ap;
	T ring = Ring_new();
	va_start(ap, x);
	for (; x; x=va_arg(ap, void*))
		Ring_addhi(ring, x);
	va_end(ap);
	return ring;
}

void Ring_free(T* ring) {
	struct node *p, *q;
	assert(ring && *ring);
	if ((p=(*ring)->head) != NULL) {
		int n = (*ring)->length;
		for (; n-- > 0; p = q) {
			q = p->link;
			FREE(p);
		}
	}
	FREE(*ring);
}

int Ring_length(T ring) {
	assert(ring);
	return ring->length;
}

void* Ring_get(T ring, int i) {
	struct node* q;
	assert(ring);
	assert(i >= 0 && i < ring->length);

	// q <- ith node
	{
		int n;
		q = ring->head;
		if (i <= ring->length / 2)
			for (n = i; n-- > 0; )
				q = q->rlink;
		else 
			for (n = ring->length - i; n-- > 0; )
				q = q->llink;
	}

	return q->value;
}

void* Ring_put(T ring, int i, void* x) {
	struct node* q;
	void* prev;
	assert(ring);
	assert(i >= 0 && i < ring->length);

	// q <- ith node
	{
		int n;
		q = ring->head;
		if (i <= ring->length / 2)
			for (n = i; n-- > 0; )
				q = q->rlink;
		else 
			for (n = ring->length - i; n-- > 0; )
				q = q->llink;
	}

	prev = q->value;
	q->value = x;
	return prev;
}

void* Ring_addhi(T ring, void* x) {
	struct node *p, *q;
	assert(ring);
	NEW(p);
	if ((q = ring->head) != NULL) {
		// insert p to the left of q
		p->llink = q->llink;
		q->llink->rlink = p;
		p->rlink = q;
		q->llink = p;
	}
	else {
		// make p ring's only value
		ring->head = p->llink = p->rlink = p;
	}

	ring->length++;
	return p->value = x;
}

void* Ring_addlo(T ring, void* x) {
	assert(ring);
	Ring_addhi(ring, x);
	ring->head = ring->head->llink;
	return x;
}

void* Ring_add(T ring, int pos, void* x) {
	assert(ring);
	assert(pos >= -ring->length && pos <= ring->length + 1);
	if (pos == 1 || pos == -ring->length) {
		return Ring_addlo(ring, x);
	}
	else if (pos == 0 || pos == ring->length + 1) {
		return Ring_addhi(ring ,x);
	}
	else {
		struct node *p, *q;
		int i = pos < 0 ? pos + ring->length : pos - 1;

		// q <- ith node
		{
			int n;
			q = ring->head;
			if (i <= ring->length / 2)
				for (n = i; n-- > 0; )
					q = q->rlink;
			else 
				for (n = ring->length - i; n-- > 0; )
					q = q->llink;
		}

		NEW(p);

		// insert p to the left of q
		p->llink = q->llink;
		q->llink->rlink = p;
		p->rlink = q;
		q->llink = p;

		ring->length++;
		return p->value = x;
	}
}


