#include <stdio.h>
#include "range.h"

void check_int(int i, int target) {
	if (i == target) printf("==> success\n");
	else printf("==> failure\n");
}

void check_str(const char* s, const char* target) {
	if (strcmp(s, target) == 0) printf("==> success\n");
	else printf("==> failure\n");
}

int main() {
	{
		char tmpFileName[L_tmpnam + 1];
		tmpnam(tmpFileName);

		FILE* fp = fopen(tmpFileName, "w");
		fputs("1231\n", fp);
		fputs("1\n", fp);
		fputs("441\n", fp);

		check_int(0, fclose(fp));
		check_int(1230, range(tmpFileName));
	}
	{
		char tmpFileName[L_tmpnam + 1];
		tmpnam(tmpFileName);

		FILE* fp = fopen(tmpFileName, "w");
		check_int(0, fclose(fp));
		check_int(1, range(tmpFileName));
	}
	//getchar();
}
