//
//  Created by huanghaifeng on 15-11-24.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#ifndef AGILE_MEM_HEADER
#define AGILE_MEM_HEADER

#include <stddef.h>
#include <stdlib.h>

void* agile_aligned_malloc(size_t len, size_t align);
void agile_aligned_free(void* p);

int** agile_alloc2d_int(int rows, int cols);

char* agile_strclone(const char* str);
char* agile_strcombine(const char* str1, const char* str2);

#endif


