#include <stdlib.h>
#include "test_common.h"

char* get_data(int i) {
	char* data1 = (char*)malloc(32);
	sprintf(data1, "helloworld%d", i);
	return data1;
}

int string_match(const void* data1, const void* data2) {
	if (strcmp((char*)data1, (char*)data2)==0) return 1;
	return 0;
}

int string_compare(const void* data1, const void* data2) {
	return strcmp((char*)data1, (char*)data2);
}
