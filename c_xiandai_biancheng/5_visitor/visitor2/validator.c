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

void acceptRange(Validator* pThis, ValidatorVisitor* pVisitor) {
	pVisitor->visitRange(pVisitor, (RangeValidator*)pThis);
}

void acceptPrevious(Validator* pThis, ValidatorVisitor* pVisitor) {
	pVisitor->visitPreviousValue(pVisitor, (PreviousValueValidator*)pThis);
}

