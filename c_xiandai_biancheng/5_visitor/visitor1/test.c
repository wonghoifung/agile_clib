#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "validator.h"

void check_int(int i, int target) {
	if (i == target) printf("==> success\n");
	else printf("==> failure\n");
}

int main() {
	{
		RangeValidator v = newRangeValidator(0, 9);
		char buf[32];
		v.base.view(&v.base, buf, sizeof buf);
		check_int(0, strcmp("Range(0-9)", buf));
		//printf("%s %d %d\n", buf,v.min,v.max);
	}

	{
		PreviousValueValidator v = newPreviousValueValidator;
		char buf[32];
		v.base.validate(&v.base, 778);
		v.base.view(&v.base, buf, sizeof(buf));
		check_int(0, strcmp("Previous(778)", buf));
	}
}
