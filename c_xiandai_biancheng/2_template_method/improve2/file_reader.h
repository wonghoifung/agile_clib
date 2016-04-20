#ifndef file_reader_header
#define file_reader_header

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct FileReaderContext {
		const char* const pFname;
		void (*const processor)(struct FileReaderContext* pThis, FILE* fp);
	} FileReaderContext;

	int read_file(FileReaderContext* pFileCtx);

#ifdef __cplusplus
}
#endif

#endif
