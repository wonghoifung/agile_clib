#include "agile_mem.h"

void* agile_aligned_malloc(size_t len, size_t align)
{
    void* p = NULL;
    void** ap = NULL;
    int offset = align - 1 + sizeof(void*);
    p = (void*)malloc(len + offset);
    if (p == NULL) return NULL;
    ap = (void**)( ((size_t)(p) + offset) & ~(align - 1) );
    ap[-1] = p;
    return ap;
}

void agile_aligned_free(void* ap)
{
    void* p = ((void**)ap)[-1];
    free(p);
}

int** agile_alloc2d_int(int rows, int cols)
{
    int i = 0;
    int header = rows * sizeof(int*);
    int data = rows * cols * sizeof(int);
    int** rowptr = (int**)malloc(header + data);
    if (rowptr == NULL) return NULL;
    int* buf = (int*)(rowptr + rows);
    for (i = 0; i < rows; ++i)
    {
        rowptr[i] = buf + i * cols;
    }
    return rowptr;
}


