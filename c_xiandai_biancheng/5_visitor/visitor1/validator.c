#include <stdbool.h>
#include <stdio.h>
#include "validator.h"

bool validateRange(Validator* pThis, int val) {
	RangeValidator* p = (RangeValidator*)pThis;
	return p->min <= val && val <= p->max;
}

bool validatePrevious(Validator* pThis, int val) {
	PreviousValueValidator* p = (PreviousValueValidator*)pThis;
	if (val < p->previousValue) return false;
	p->previousValue = val;
	return true;
}

void viewRange(Validator* pThis, char* pBuf, size_t size) {
	RangeValidator* p = (RangeValidator*)pThis;
	snprintf(pBuf, size, "Range(%d-%d)", p->min, p->max);
}

void viewPrevious(Validator* pThis, char* pBuf, size_t size) {
	PreviousValueValidator* p = (PreviousValueValidator*)pThis;
	snprintf(pBuf, size, "Previous(%d)", p->previousValue);
}

