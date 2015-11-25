//
//  Created by huanghaifeng on 15-11-24.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#include "agile_mem.h"
#include <string.h>

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

char* agile_strclone(const char* str)
{
	size_t l = strlen(str);
	char* s = malloc(l + 1);
	memcpy(s, str, l + 1);
	return s;
}

char* agile_strcombine(const char* str1, const char* str2)
{
	size_t l1 = strlen(str1);
	size_t l2 = strlen(str2);
	char* s = malloc(l1 + l2 + 1);
	memcpy(s, str1, l1);
	memcpy(s + l1, str2, l2 + 1);
	return s;
}
