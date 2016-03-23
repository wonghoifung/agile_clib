#ifndef ARENA_HEADER
#define ARENA_HEADER

#include "except.h"

#define T Arena_T

typedef struct T* T;

extern const Except_T Arena_NewFailed;
extern const Except_T Arena_Failed;

// functions
extern T Arena_new(void);
extern void Arena_dispose(T* ap);
extern void* Arena_alloc(T arena, long nbytes, const char* file, int line);
extern void* Arena_calloc(T arena, long count, long nbytes, const char* file, int line);
extern void Arena_free(T arena);

#define AALLOC(arena,nbytes) Arena_alloc((arena),(nbytes),__FILE__,__LINE__)
#define ACALLOC(arena,count,nbytes) Arena_calloc((arena),(count),(nbytes),__FILE__,__LINE__)

#undef T

#endif
