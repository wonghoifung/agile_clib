#ifndef SET_HEADER
#define SET_HEADER

#define T Set_T

typedef struct T* T;

// exported functions
extern T Set_new(int hint, int cmp(const void* x, const void* y), unsigned hash(const void* x));
extern void Set_free(T* set);

#undef T

#endif

