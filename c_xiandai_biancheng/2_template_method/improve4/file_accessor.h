#ifndef file_accessor_header
#define file_accessor_header

#include <stdio.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct FileAccessorContext {
		FILE* fp;
		const char* const pFname;
		const char* const pMode;
		bool (*const processor)(struct FileAccessorContext* pThis);
	} FileAccessorContext;

	bool access_file(FileAccessorContext* pThis);
	FILE* get_file_pointer(FileAccessorContext* pThis);

	#define NEW_FILE(pFname, pMode, processor) {NULL,(pFname),(pMode),(processor)}

#ifdef __cplusplus
}
#endif

#endif
