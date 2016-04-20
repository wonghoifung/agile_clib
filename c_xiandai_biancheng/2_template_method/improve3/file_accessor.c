#include "file_accessor.h"

bool access_file(FileAccessorContext* pFileCtx) {
	FILE* fp = fopen(pFileCtx->pFname, pFileCtx->pMode);
	if (fp == NULL) return false;
	pFileCtx->processor(pFileCtx, fp);
	fclose(fp);
	return true;
}
