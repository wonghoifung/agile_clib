#include <stdio.h>
#include <stdbool.h>
#include "array_list.h"
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
		void* table[2];
		ArrayList buf = new_array_list(table);

		check_int(2, buf.capacity);
		check_int((size_t)0, buf.size(&buf));
		check_int(table, buf.pBuf);

		char str1[] = "hello";
		buf.add(&buf, str1);

		check_int(2, buf.capacity);
		check_int((size_t)1, buf.size(&buf));
		check_int(table, buf.pBuf);

		char str2[] = "world";
		buf.add(&buf, str2);

		check_int(2, buf.capacity);
		check_int((size_t)2, buf.size(&buf));
		check_int(table, buf.pBuf);

		//check_int(str1, buf.remove(&buf, str1));
		check_str(str1, (char*)buf.remove(&buf, str1));

		check_int(2, buf.capacity);
		check_int((size_t)1, buf.size(&buf));
		check_str(str2, (char*)buf.get(&buf, 0));

		check_int(NULL, buf.remove(&buf, str1));

		check_int(2, buf.capacity);
		check_int((size_t)1, buf.size(&buf));
		check_str(str2, (char*)buf.get(&buf, 0));

		//check_int(str2, buf.remove(&buf, str2));
		check_str(str2, (char*)buf.remove(&buf, str2));

		check_int(2, buf.capacity);
		check_int((size_t)0, buf.size(&buf));

		check_int(NULL, buf.remove(&buf, str2));
	}

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
		int_sorter("--------------xxxxxxxxxxxxxxxxxxxxx");
	}
}
