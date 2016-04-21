#ifndef file_accessor_header
#define file_accessor_header

#include <stdio.h>
#include <stdbool.h>
#include "buffer.h"
#include "array_list.h"

#ifdef __cplusplus
extern "C" {
#endif

	struct FileAccessorContext;

	typedef struct FileErrorObserver {
		void (*const onError)(struct FileErrorObserver* pThis, struct FileAccessorContext* pFileCtx);
	} FileErrorObserver;

	typedef struct FileAccessorContext {
		FILE* fp;
		const char* const pFname;
		const char* const pMode;
		ArrayList observer_table;
		bool (*const processor)(struct FileAccessorContext* pThis);
	} FileAccessorContext;

	bool access_file(FileAccessorContext* pThis);
	FILE* get_file_pointer(FileAccessorContext* pThis);

	long file_size(FileAccessorContext* pThis);
	long file_current_pos(FileAccessorContext* pThis);
	int set_file_pos(FileAccessorContext* pThis, long offset, int whence);
	bool read_file(FileAccessorContext* pThis, BufferContext* pBufCtx);
	bool write_file(FileAccessorContext* pThis, BufferContext* pBufCtx);
	void add_file_error_observer(FileAccessorContext* pThis, FileErrorObserver* pErrorObserver);
	void remove_file_error_observer(FileAccessorContext* pThis, FileErrorObserver* pErrorObserver);

#ifdef __cplusplus
}
#endif

#endif
