#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "int_sorter.h"
#include "file_accessor.h"
#include "buffer.h"

static bool reader(FileAccessorContext* pThis);
static bool do_with_buffer(BufferContext* p);
static bool writer(FileAccessorContext* pThis);
static int comparator(const void* p1, const void* p2);
static void file_error(FileErrorObserver *pThis, FileAccessorContext *pFileCtx);

typedef struct {
	BufferContext base;
	SortContext* pAppCtx;
} MyBufferContext;

typedef struct {
	FileAccessorContext base;
	MyBufferContext* pBufCtx;
} MyFileAccessorContext;

static FileErrorObserver file_error_observer = { file_error };

IntSorterError int_sorter(const char* pFname) {
	SortContext ctx = { pFname, 0, 0, ERR_CAT_OK };

	MyBufferContext bufCtx = { { NULL, 0, do_with_buffer }, &ctx };
	buffer(&bufCtx.base);

	return ctx.errorCategory;
}

static bool do_with_buffer(BufferContext* p) {
	MyBufferContext* pBufCtx = (MyBufferContext*)p;

	MyFileAccessorContext readFileCtx = { { NULL, pBufCtx->pAppCtx->pFname, "rb", reader, &file_error_observer }, pBufCtx };
	if (!access_file(&readFileCtx.base)) {
		//file_error(pBufCtx->pAppCtx);
		return false;
	}

	qsort(p->pBuf, p->size / sizeof(int), sizeof(int), comparator);

	MyFileAccessorContext writeFileCtx = { { NULL, pBufCtx->pAppCtx->pFname, "wb", writer, &file_error_observer }, pBufCtx };
	if (!access_file(&writeFileCtx.base)) {
		//file_error(pBufCtx->pAppCtx);
		return false;
	}

	return true;
}

static bool reader(FileAccessorContext* pThis) {
	MyFileAccessorContext* pFileCtx = (MyFileAccessorContext*)pThis;
	
	long size = file_size(pThis);
	if (size == -1) {
		//file_error(pBufCtx->pAppCtx);
		return false;
	}

	if (!allocate_buffer(&pFileCtx->pBufCtx->base, size)) {
		pFileCtx->pBufCtx->pAppCtx->errorCategory = ERR_CAT_MEMORY;
		return false;
	}

	return read_file(pThis, &pFileCtx->pBufCtx->base);
}

static bool writer(FileAccessorContext* pThis) {
	MyFileAccessorContext* pFileCtx = (MyFileAccessorContext*)pThis;
	return write_file(pThis, &pFileCtx->pBufCtx->base);
}

static int comparator(const void* p1, const void* p2) {
	int i1 = *(const int*)p1;
	int i2 = *(const int*)p2;
	if (i1 < i2) return -1;
	if (i1 > i2) return 1;
	return 0;
}

static void file_error(FileErrorObserver *pThis, FileAccessorContext *pFileCtx) {
	default_file_error_observer.onError(pThis, pFileCtx);
	MyFileAccessorContext* pMyFileCtx = (MyFileAccessorContext*)pFileCtx;
	pMyFileCtx->pBufCtx->pAppCtx->errorCategory = ERR_CAT_FILE;
}
