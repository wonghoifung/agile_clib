#include <stdio.h>
#include <stdbool.h>
#include "int_sorter.h"

void check_bool(bool b, bool target) {
	if (b == target) printf("==> success\n");
	else printf("==> failure\n");
}

void check_int(int i, int target) {
	if (i == target) printf("==> success\n");
	else printf("==> failure\n");
}

void check_str(const char* s, const char* target) {
	if (strcmp(s, target) == 0) printf("==> success\n");
	else printf("==> failure\n");
}

static bool write_int(FILE* fp, int i) {
	return fwrite(&i, sizeof(int), 1, fp) == 1;
}

static int read_int(FILE* fp) {
	int ret;
	fread(&ret, sizeof(int), 1, fp);
	return ret;
}

int main() {
	{
		char tmpFileName[L_tmpnam + 1];
		tmpnam(tmpFileName);

		FILE* fp = fopen(tmpFileName, "wb");
		check_bool(true, write_int(fp, 1231));
		check_bool(true, write_int(fp, 1));
		check_bool(true, write_int(fp, 441));
		check_int(0, fclose(fp));

		int_sorter(tmpFileName);

		fp = fopen(tmpFileName, "rb");
		check_int(1, read_int(fp));
		check_int(441, read_int(fp));
		check_int(1231, read_int(fp));
		check_int(0, fclose(fp));
	}

	{
		char tmpFileName[L_tmpnam + 1];
		tmpnam(tmpFileName);

		FILE* fp = fopen(tmpFileName, "w");
		check_int(0, fclose(fp));

		int_sorter(tmpFileName);
	}

	{
		int_sorter("-------------- non existent file");
	}
}
