#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "ap.h"
#include "fmt.h"
#include "xp.h"
#include "mem.h"

#define T AP_T

struct T {
	int sign;
	int ndigits;
	int size;
	XP_T digits;
};

// macros
#define iszero(x) ((x)->ndigits == 1 && (x)->digits[0] == 0)
#define maxdigits(x,y) ((x)->ndigits > (y)->ndigits ? (x)->ndigits : (y)->ndigits)

// prototypes
static T normalize(T z, int n);

// static functions
static T mk(int size) {
	T z = CALLOC(1, sizeof (*z) + size);
	assert(size > 0);
	z->sign = 1;
	z->size = size;
	z->ndigits = 1;
	z->digits = (XP_T)(z + 1);
	return z;
}

static T set(T z, long int n) {
	if (n == LONG_MIN)
		XP_fromint(z->size, z->digits, LONG_MAX + 1UL);
	else if (n < 0)
		XP_fromint(z->size, z->digits, -n);
	else 
		XP_fromint(z->size, z->digits, n);
	z->sign = n < 0 ? -1 : 1;
	return normalize(z, z->size);
}

static T normalize(T z, int n) {
	z->ndigits = XP_length(n, z->digits);
	return z;
}

static T add(T z, T x, T y) {
	int n = y->ndigits;
	if (x->ndigits < n) {
		return add(z, y, x);
	} else if (x->ndigits > n) {
		int carry = XP_add(n, z->digits, x->digits, y->digits, 0);
		z->digits[z->size - 1] = XP_sum(x->ndigits - n, &z->digits[n], &x->digits[n], carry);
	} else {
		z->digits[n] = XP_add(n, z->digits, x->digits, y->digits, 0);
	}
	return normalize(z, z->size);
}

// functions
T AP_new(long int n) {
	return set(mk(sizeof (long int)), n);
}

void AP_free(T* z) {
	assert(z && *z);
	FREE(*z);
}

T AP_neg(T x) {
	T z;
	assert(x);
	z = mk(x->ndigits);
	memcpy(z->digits, x->digits, x->ndigits);
	z->ndigits = x->ndigits;
	z->size = iszero(z) ? 1 : -x->sign;
	return z;
}

T AP_mul(T x, T y) {
	T z;
	assert(x);
	assert(y);
	z = mk(x->ndigits + y->ndigits);
	XP_mul(z->digits, x->ndigits, x->digits, y->ndigits, y->digits);
	normalize(z, z->size);
	z->sign = iszero(z) || /* x and y have the same sign */((x->sign ^ y->sign) == 0) ? 1 : -1;
	return z;
}

T AP_add(T x, T y) {
	T z;
	assert(x);
	assert(y);
	if ((x->sign ^ y->sign) == 0) {
		z = add(mk(maxdigits(x,y) + 1), x, y);
		z->sign = iszero(z) ? 1 : x->sign;
	} else {
		// set z to x + y when x and y have different signs
		if (cmp(x, y) > 0) {
			z = sub(mk(x->ndigits), x, y);
			z->sign = iszero(z) ? 1 : x->sign;
		}
	}
	return z;
}
