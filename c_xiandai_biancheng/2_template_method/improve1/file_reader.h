#ifndef file_reader_header
#define file_reader_header

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

	int read_file(const char* pFname, int (*processor)(FILE* fp));

#ifdef __cplusplus
}
#endif

#endif
