#ifndef AGILE_MEM_HEADER
#define AGILE_MEM_HEADER

#include <stddef.h>
#include <stdlib.h>

void* agile_aligned_malloc(size_t len, size_t align);
void agile_aligned_free(void* p);

int** agile_alloc2d_int(int rows, int cols);

#endif


