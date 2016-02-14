#ifndef test_common_header
#define test_common_header

#include <stdio.h>

static char* get_data(int i) {
	char* data1 = (char*)malloc(32);
	sprintf(data1, "helloworld%d", i);
	return data1;
}

#endif

