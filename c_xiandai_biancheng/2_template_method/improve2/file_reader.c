#include "file_reader.h"

int read_file(FileReaderContext* pFileCtx) {
	FILE* fp = fopen(pFileCtx->pFname, "r");
	if (fp == NULL) return -1;
	pFileCtx->processor(pFileCtx, fp);
	fclose(fp);
	return 0;
}
