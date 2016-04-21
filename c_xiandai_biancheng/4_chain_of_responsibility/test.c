#include <stdbool.h>
#include <stdio.h>
#include "stack.h"

typedef struct TestValidator {
	Validator base;
	bool result;
} TestValidator;

static bool validateTest(Validator* p, int val) {
	TestValidator* pThis = (TestValidator*)p;
	return pThis->result;
}

static TestValidator trueValidator = { { validateTest }, true };
static TestValidator falseValidator = { { validateTest }, false };

void check_int(int i, int target) {
	if (i == target) printf("==> success\n");
	else printf("==> failure\n");
}

void check_bool(bool b, bool target) {
	if (b == target) printf("==> success\n");
	else printf("==> failure\n");
}

int main() {
	{
		int buf[16];
		Stack stack = newStack(buf);
		check_bool(false, pop(&stack, 0));
	}

	{
		int buf[16];
		Stack stack = newStack(buf);

		check_bool(true, push(&stack, 123));

		int ret;
		check_bool(true, pop(&stack, &ret));
		check_int(123, ret);

		check_bool(false, pop(&stack, &ret));
	}

	{
		int buf[16];
		Stack stack = newStack(buf);

		for (int i = 0; i < 16; ++i) push(&stack, i);
		check_bool(false, push(&stack, 100));

		int ret;
		check_bool(true, pop(&stack, &ret));
		check_int(15, ret);
	}

	{
		int buf[16];
		RangeValidator validator = newRangeValidator(0, 9);
		Stack stack = newStackWithValidator(buf, &validator.base);
		check_bool(false, push(&stack, -1));
		check_bool(false, push(&stack, 10));
	}

	{
		int buf[16];
		PreviousValueValidator validator = newPreviousValueValidator;
		Stack stack = newStackWithValidator(buf, &validator.base);
		check_bool(true, push(&stack, 3));
		check_bool(false, push(&stack, 2));
	}

	{
		ChainedValidator trueChainedValidator = newChainedValidator(&trueValidator.base, NULL);
		check_bool(true, trueChainedValidator.base.validate(&trueChainedValidator.base, 0));

		ChainedValidator falseChainedValidator = newChainedValidator(&falseValidator.base, NULL);
		check_bool(false, falseChainedValidator.base.validate(&falseChainedValidator.base, 0));
	}

	{
		ChainedValidator falseChain = newChainedValidator(&falseValidator.base, NULL);
		ChainedValidator trueFalseChain = newChainedValidator(&trueValidator.base, &falseChain.base);
		check_bool(false, trueFalseChain.base.validate(&trueFalseChain.base, 0));
	}

	{
		ChainedValidator trueChain = newChainedValidator(&trueValidator.base, NULL);
		ChainedValidator falseTrueChain = newChainedValidator(&falseValidator.base, &trueChain.base);
		check_bool(false, falseTrueChain.base.validate(&falseTrueChain.base, 0));
	}

	{
		ChainedValidator trueChain = newChainedValidator(&trueValidator.base, NULL);
		ChainedValidator trueTrueChain = newChainedValidator(&trueValidator.base, &trueChain.base);
		check_bool(true, trueTrueChain.base.validate(&trueTrueChain.base, 0));
	}

	{
		ChainedValidator falseChain = newChainedValidator(&falseValidator.base, NULL);
		ChainedValidator falseFalseChain = newChainedValidator(&falseValidator.base, &falseChain.base);
		check_bool(false, falseFalseChain.base.validate(&falseFalseChain.base, 0));
	}

	{
		RangeValidator rangeValidator = newRangeValidator(0, 9);
		PreviousValueValidator preValidator = newPreviousValueValidator;
		ChainedValidator preChain = newChainedValidator(&preValidator.base, NULL);
		ChainedValidator rangeChain = newChainedValidator(&rangeValidator.base, &preChain);
		int buf[16];
		Stack stack = newStackWithValidator(buf, &rangeChain.base);
		check_bool(false, push(&stack, -1));
		check_bool(true, push(&stack, 5));
		check_bool(false, push(&stack, 4));
		check_bool(true, push(&stack, 9));
		check_bool(false, push(&stack, 10));
	}
}
